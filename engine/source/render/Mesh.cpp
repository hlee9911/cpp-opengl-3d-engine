#include "render/Mesh.h"
#include "graphics/GraphicsAPI.h"
#include "Engine.h"

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

namespace eng
{
	Mesh::Mesh(const VertexLayout& layout, 
		const List<float>& verticies,
		const List<uint32_t>& indicies) noexcept
	{
		m_VertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		// create VBO and EBO
		m_VBO = graphicsAPI.CreateVertexBuffer(verticies);
		m_EBO = graphicsAPI.CreateIndexBuffer(indicies);

		// generate and bind VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		for (auto& element : m_VertexLayout.elements)
		{
			glVertexAttribPointer(
				element.index,
				element.size,
				element.type,
				GL_FALSE,
				m_VertexLayout.stride,
				(void*)(uintptr_t)element.offset
			);
			glEnableVertexAttribArray(element.index);
		}

		// bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		// unbind VAO, VBO, EBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_VertexCount = (verticies.size() * sizeof(float)) / m_VertexLayout.stride;
		m_IndexCount = indicies.size();
	}

	Mesh::Mesh(const VertexLayout& layout, 
		const List<float>& verticies) noexcept
	{
		m_VertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

		// create VBO
		m_VBO = graphicsAPI.CreateVertexBuffer(verticies);

		// generate and bind VAO
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		for (auto& element : m_VertexLayout.elements)
		{
			glVertexAttribPointer(
				element.index,
				element.size,
				element.type,
				GL_FALSE,
				m_VertexLayout.stride,
				(void*)(uintptr_t)element.offset
			);
			glEnableVertexAttribArray(element.index);
		}

		// unbind VAO, VBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_VertexCount = (verticies.size() * sizeof(float)) / m_VertexLayout.stride;
	}

	void Mesh::Bind()
	{
		glBindVertexArray(m_VAO);
	}

	void Mesh::Draw()
	{
		if (m_IndexCount > 0)
		{
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
		}
	}

	shared<Mesh> Mesh::Load(const std::string& path)
	{
		auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);

		if (contents.empty()) return nullptr;

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

		cgltf_options options = {};
		cgltf_data* data = nullptr;

		cgltf_result res = cgltf_parse(&options, contents.data(), contents.size(), &data);

		if (res != cgltf_result_success) return nullptr;

		auto fullPath = Engine::GetInstance().GetFileSystem().GetAssetsFolder() / path;
		// need to find and load the .bin buffer

		// load binary buffer
		// and convert the folder string().c_str()
		res = cgltf_load_buffers(&options, data, fullPath.remove_filename().string().c_str());
	
		if (res != cgltf_result_success)
		{
			cgltf_free(data);
			return nullptr;
		}

		shared<Mesh> result = nullptr;

		for (cgltf_size mi = 0; mi < data->meshes_count; ++mi)
		{
			auto& mesh = data->meshes[mi];
			for (cgltf_size pi = 0; pi < mesh.primitives_count; ++pi)
			{
				auto& primitive = mesh.primitives[pi];
				if (primitive.type != cgltf_primitive_type_triangles)
				{
					continue;
				}

				VertexLayout vertexLayout;
				cgltf_accessor* accessors[3] = { nullptr, nullptr, nullptr };

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

				// allocate the buffer

				if (!accessors[VertexElement::PositionIndex]) continue;

				auto vertexCount = accessors[VertexElement::PositionIndex]->count;

				List<float> verticies;
				verticies.resize((vertexLayout.stride / sizeof(float)) * vertexCount);

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

				if (primitive.indices)
				{
					auto indexCount = primitive.indices->count;
					List<uint32_t> indicies(indexCount);
					for (cgltf_size i = 0; i < indexCount; ++i)
					{
						indicies[i] = readIndex(primitive.indices, i);
					}
					result = std::make_shared<Mesh>(vertexLayout, verticies, indicies);
				}
				else
				{
					result = std::make_shared<Mesh>(vertexLayout, verticies);
				}

				if (result) break;
			}

			if (result) break;
		}

		cgltf_free(data);

		return result;
	}
}
