#include "scene/GameObject.h"
#include "scene/components/MeshComponent.h"
#include "scene/components/AnimationComponent.h"
#include "graphics/VertexLayout.h"
#include "graphics/Texture.h"
#include "render/Material.h"
#include "render/Mesh.h"
#include "Engine.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

namespace eng
{
	void GameObject::Update(float deltaTime)
	{
		if (!m_Active) return;

		for (auto& component : m_Components)
		{
			component->Update(deltaTime);
		}

		for (auto it = m_Children.begin(); it != m_Children.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = m_Children.erase(it);
			}
		}
	}

	const std::string& GameObject::GetName() const noexcept
	{
		return m_Name;
	}

	void GameObject::SetName(const std::string& name) noexcept
	{
		m_Name = name;
	}

	GameObject* GameObject::GetParent() noexcept
	{
		return m_Parent;
	}

	bool GameObject::SetParent(GameObject* parent)
	{
		if (!m_Scene) return false;
		return m_Scene->SetParent(this, parent);
	}

	bool GameObject::IsAlive() const noexcept
	{
		return m_IsAlive;
	}

	void GameObject::MarkForDestroy()
	{
		m_IsAlive = false;
	}

	void GameObject::AddComponenet(Component* component)
	{
		m_Components.emplace_back(component);
		component->m_Owner = this;
	}

	GameObject* GameObject::FindChildByName(const std::string& name)
	{
		if (m_Name == name) return this;

		// recursively search in children
		for (auto& child : m_Children)
		{
			if (auto res = child->FindChildByName(name))
			{
				return res;
			}
		}

		return nullptr;
	}

	const glm::vec3& GameObject::GetPosition() const noexcept
	{
		return m_Position;
	}

	glm::vec3 GameObject::GetWorldPosition() const
	{
		glm::vec4 hom = GetWorldTransform() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return glm::vec3(hom) / hom.w;
	}

	void GameObject::SetPosition(const glm::vec3& pos) noexcept
	{
		m_Position = pos;
	}

	const glm::quat& GameObject::GetRotation() const noexcept
	{
		return m_Rotation;
	}

	void GameObject::SetRotation(const glm::quat& rot) noexcept
	{
		m_Rotation = rot;
	}

	const glm::vec3& GameObject::GetScale() const noexcept
	{
		return m_Scale;
	}

	void GameObject::SetScale(const glm::vec3& scale) noexcept
	{
		m_Scale = scale;
	}

	glm::mat4 GameObject::GetLocalTransform() const
	{
		// identity matrix
		glm::mat4 mat = glm::mat4(1.0f);

		// Translation
		mat = glm::translate(mat, m_Position);

		// Rotation
		// Use single entity called quaternion instead of three different angles
		mat = mat * glm::mat4_cast(m_Rotation);

		// Scale
		mat = glm::scale(mat, m_Scale);
		
		return mat;
	}

	glm::mat4 GameObject::GetWorldTransform() const
	{
		if (m_Parent)
		{
			return m_Parent->GetWorldTransform() * GetLocalTransform();
		}
		return GetLocalTransform();
	}

	/// <summary>
	/// Parses a cgltf_node and creates a corresponding GameObject in the scene. It handles the node's transformation 
	/// (either as a matrix or separate TRS components) and its mesh data if available. 
	/// The function is called recursively for each child node to build the entire hierarchy of GameObjects.
	/// </summary>
	/// <param name="node"></param>
	/// <param name="parent"></param>
	/// <param name="folder"></param>
	void ParseGLTFNode(cgltf_node* node, GameObject* parent, const std::filesystem::path& folder)
	{
		auto object = parent->GetScene()->CreateGameObject(node->name, parent);
		
		// transform can be stored as a matrix or separate TRS components
		if (node->has_matrix)
		{
			auto mat = glm::make_mat4(node->matrix);
			glm::vec3 translation, scale, skew;
			glm::vec4 perspective;
			glm::quat orientation;
			glm::decompose(mat, scale, orientation, translation, skew, perspective);

			object->SetPosition(translation);
			object->SetRotation(orientation);
			object->SetScale(scale);
		}
		else
		{
			// transform stored as separate TRS components
			// if there's no matrix, read translation, rotation, and scale separately
			if (node->has_translation)
			{
				object->SetPosition(
					glm::vec3(
						node->translation[0], 
						node->translation[1], 
						node->translation[2]
					));
			}
			if (node->has_rotation)
			{
				object->SetRotation(
					glm::quat(
						node->rotation[3], // w
						node->rotation[0], // x
						node->rotation[1], // y
						node->rotation[2]  // z
					));
			}
			if (node->has_scale)
			{
				object->SetScale(
					glm::vec3(
						node->scale[0],
						node->scale[1],
						node->scale[2]
					));
			}
		}

		if (node->mesh)
		{
			for (cgltf_size primitive_index = 0; primitive_index < node->mesh->primitives_count; ++primitive_index)
			{
				auto& primitive = node->mesh->primitives[primitive_index];
				if (primitive.type != cgltf_primitive_type_triangles)
				{
					continue;
				}

				auto readFloats = [](const cgltf_accessor* acc, cgltf_size i, float* out, int n)
					{
						std::fill(out, out + n, 0.0f);
						return cgltf_accessor_read_float(acc, i, out, n) == 1;
					};

				auto readIndex = [](const cgltf_accessor* acc, cgltf_size i)
					{
						cgltf_uint out = 0;
						cgltf_bool ok = cgltf_accessor_read_uint(acc, i, &out, 1);
						return ok ? static_cast<uint32_t>(out) : 0;
					};

				VertexLayout vertexLayout;
				cgltf_accessor* accessors[4] = { nullptr, nullptr, nullptr };

				for (cgltf_size ai = 0; ai < primitive.attributes_count; ++ai)
				{
					auto& attr = primitive.attributes[ai];
					auto acc = attr.data;
					if (!acc)
					{
						continue;
					}

					VertexElement element;
					element.type = GL_FLOAT;

					switch (attr.type)
					{
					case cgltf_attribute_type_position:
					{
						accessors[VertexElement::PositionIndex] = acc;
						element.index = VertexElement::PositionIndex;
						element.size = 3;
					}
					break;
					case cgltf_attribute_type_color:
					{
						// we only use COLOR_0 (attr.index == 0)
						if (attr.index != 0) continue;
						accessors[VertexElement::ColorIndex] = acc;
						element.index = VertexElement::ColorIndex;
						element.size = 3;
					}
					break;
					case cgltf_attribute_type_texcoord:
					{
						// we only use first index (attr.index == 0)
						if (attr.index != 0) continue;
						accessors[VertexElement::UVIndex] = acc;
						element.index = VertexElement::UVIndex;
						element.size = 2;
					}
					break;
					case cgltf_attribute_type_normal:
					{
						accessors[VertexElement::NormalIndex] = acc;
						element.index = VertexElement::NormalIndex;
						element.size = 3;
					}
					break;
					default:
						continue;
					}

					if (element.size > 0)
					{
						element.offset = vertexLayout.stride;
						vertexLayout.stride += element.size * sizeof(float);
						vertexLayout.elements.push_back(element);
					}
				}

				// calculate vertex count from position accessor (position is required, so it must be present)
				if (!accessors[VertexElement::PositionIndex]) continue;

				auto vertexCount = accessors[VertexElement::PositionIndex]->count;

				List<float> verticies;
				verticies.resize((vertexLayout.stride / sizeof(float))* vertexCount);

				for (cgltf_size vi = 0; vi < vertexCount; ++vi)
				{
					for (auto& el : vertexLayout.elements)
					{
						if (!accessors[el.index]) continue;

						auto index = (vi * vertexLayout.stride + el.offset) / sizeof(float);
						float* outData = &verticies[index];
						readFloats(accessors[el.index], vi, outData, el.size); // reads attribute for vertex vi
					}
				}

				shared<Mesh> mesh;
				if (primitive.indices)
				{
					auto indexCount = primitive.indices->count;
					List<uint32_t> indicies(indexCount);
					for (cgltf_size i = 0; i < indexCount; ++i)
					{
						indicies[i] = readIndex(primitive.indices, i);
					}
					mesh = std::make_shared<Mesh>(vertexLayout, verticies, indicies);
				}
				else
				{
					mesh = std::make_shared<Mesh>(vertexLayout, verticies);
				}

				// metallic-roughness material

				// specular-glossiness material (extension)

				auto mat = std::make_shared<Material>();
				mat->SetShaderProgram(Engine::GetInstance().GetGraphicsAPI().GetDefaultShaderProgram());
				
				if (primitive.material)
				{
					auto gltfMat = primitive.material;
					if (gltfMat->has_pbr_metallic_roughness)
					{
						auto pbr = gltfMat->pbr_metallic_roughness;
						auto texture = pbr.base_color_texture.texture;
						if (texture && texture->image)
						{
							if (texture->image->uri)
							{
								auto path = folder / std::string(texture->image->uri);
								auto tex = Engine::GetInstance().GetTextureManager().GetOrLoadTexture(path.string());
								mat->SetTextureParam("baseColorTexture", tex);
							}
						}
					}
					else if (gltfMat->has_pbr_specular_glossiness)
					{
						auto pbr = gltfMat->pbr_specular_glossiness;
						auto texture = pbr.diffuse_texture.texture;
						if (texture && texture->image)
						{
							if (texture->image->uri)
							{
								auto path = folder / std::string(texture->image->uri);
								auto tex = Engine::GetInstance().GetTextureManager().GetOrLoadTexture(path.string());
								mat->SetTextureParam("baseColorTexture", tex);
							}
						}
					}

					// create a meshcomponent with this mesh and material, and add it to the object
					object->AddComponenet(new MeshComponent(mat, mesh));
				}
			}
		}

		// recursively parse child nodes
		for (cgltf_size ci = 0; ci < node->children_count; ++ci)
		{
			auto childNode = node->children[ci];
			ParseGLTFNode(childNode, object, folder);
		}
	}

	auto ReadScalar = [](cgltf_accessor* acc, cgltf_size index)
	{
		float res = 0.0f;
		cgltf_accessor_read_float(acc, index, &res, 1);
		return  res;
	};

	auto ReadVec3 = [](cgltf_accessor* acc, cgltf_size index)
	{
		glm::vec3 res;
		cgltf_accessor_read_float(acc, index, glm::value_ptr(res), 3);
		return res;
	};

	auto ReadQuat = [](cgltf_accessor* acc, cgltf_size index)
	{
		float res[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		cgltf_accessor_read_float(acc, index, res, 4);
		return glm::quat(res[3], res[0], res[1], res[2]);
	};

	auto ReadTimes = [](cgltf_accessor* acc, List<float>& outTimes)
	{
		outTimes.resize(acc->count);
		for (cgltf_size i = 0; i < acc->count; ++i)
		{
			outTimes[i] = ReadScalar(acc, i);
		}
	};

	auto ReadOutputVec3 = [](cgltf_accessor* acc, List<glm::vec3>& outValues)
	{
		outValues.resize(acc->count);
		for (cgltf_size i = 0; i < acc->count; ++i)
		{
			outValues[i] = ReadVec3(acc, i);
		}
	};

	auto ReadOutputQuat = [](cgltf_accessor* acc, List<glm::quat>& outValues)
	{
		outValues.resize(acc->count);
		for (cgltf_size i = 0; i < acc->count; ++i)
		{
			outValues[i] = ReadQuat(acc, i);
		}
	};

	/// <summary>
	/// Load entire glTF scene from the specified file and create a GameObject hierarchy representing it.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	GameObject* GameObject::LoadGLTF(const std::string& path)
	{
		auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);
		if (contents.empty()) return nullptr;

		cgltf_options options = {};
		cgltf_data* data = nullptr;

		cgltf_result res = cgltf_parse(&options, contents.data(), contents.size(), &data);

		if (res != cgltf_result_success) return nullptr;

		auto fullPath = Engine::GetInstance().GetFileSystem().GetAssetsFolder() / path;
		// need to find and load the .bin buffer

		auto fullFolderPath = fullPath.remove_filename();
		auto relativeFolderPath = std::filesystem::path(path).remove_filename();
		
		// load binary buffer
		// and convert the folder string().c_str()
		res = cgltf_load_buffers(&options, data, fullFolderPath.string().c_str());

		if (res != cgltf_result_success)
		{
			cgltf_free(data);
			return nullptr;
		}

		auto resultObject = Engine::GetInstance().GetScene()->CreateGameObject("Result");
		auto scene = &data->scenes[0];

		for (cgltf_size i = 0; i < scene->nodes_count; ++i)
		{
			auto node = scene->nodes[i];
			ParseGLTFNode(node, resultObject, relativeFolderPath);
		}

		List<shared<AnimationClip>> clips;
		for (cgltf_size ai = 0; ai < data->animations_count; ++ai)
		{
			auto& anim = data->animations[ai];

			auto clip = std::make_shared<AnimationClip>();
			clip->name = anim.name ? anim.name : "noname";
			clip->duration = 0.0f;

			Dictionary<cgltf_node*, size_t> trackIndexOf;

			auto GetOrCreateTrack = [&](cgltf_node* node) -> TransformTrack&
				{
					// find track for this node, if it doesn't exist, create a new one
					auto it = trackIndexOf.find(node);
					if (it != trackIndexOf.end())
					{
						return clip->tracks[it->second];
					}

					// if not found, create a new track for this node
					TransformTrack track;
					track.targetName = node->name;
					clip->tracks.push_back(track);
					size_t idx = clip->tracks.size() - 1;
					trackIndexOf[node] = idx;
					return clip->tracks[idx];
				};

			// iterate through channels to read keyframe data
			for (cgltf_size ci = 0; ci < anim.channels_count; ++ci)
			{
				auto& channel = anim.channels[ci];
				auto sampler = channel.sampler;

				if (!channel.target_node || !sampler || !sampler->input || !sampler->output) continue;

				List<float> times;
				ReadTimes(sampler->input, times);

				auto& track = GetOrCreateTrack(channel.target_node);

				// manages three different animations types: translation, rotation, and scale
				switch (channel.target_path)
				{
					case cgltf_animation_path_type_translation:
					{
						List<glm::vec3> values;
						ReadOutputVec3(sampler->output, values);
						track.positions.resize(times.size());
						// times and values should have the same count, but we check times.size() just in case
						for (size_t i = 0; i < times.size(); ++i)
						{
							track.positions[i].time = times[i];
							track.positions[i].value = values[i];
						}
					}
						break;
					case cgltf_animation_path_type_rotation:
					{
						List<glm::quat> values;
						ReadOutputQuat(sampler->output, values);
						track.rotations.resize(times.size());
						// times and values should have the same count, but we check times.size() just in case
						for (size_t i = 0; i < times.size(); ++i)
						{
							track.rotations[i].time = times[i];
							track.rotations[i].value = values[i];
						}
					}
						break;
					case cgltf_animation_path_type_scale:
					{
						List<glm::vec3> values;
						ReadOutputVec3(sampler->output, values);
						track.scales.resize(times.size());
						// times and values should have the same count, but we check times.size() just in case
						for (size_t i = 0; i < times.size(); ++i)
						{
							track.scales[i].time = times[i];
							track.scales[i].value = values[i];
						}
					}
						break;
					default:
						break;
				}

				// update clip duration based on the last keyframe time
				clip->duration = std::max(clip->duration, times.back());
			}

			clips.push_back(std::move(clip));
		}

		// if we have any animation clips, create an AnimationComponent and register the clips
		if (!clips.empty())
		{
			auto animComponent = new AnimationComponent();
			resultObject->AddComponenet(animComponent);
			for (auto& clip : clips)
			{
				animComponent->RegisterClip(clip->name, clip);
			}
		}

		cgltf_free(data);

		return resultObject;
	}
}
