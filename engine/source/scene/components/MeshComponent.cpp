#include "scene/components/MeshComponent.h"
#include "scene/GameObject.h"
#include "render/Material.h"
#include "render/Mesh.h"
#include "render/RenderQueue.h"
#include "Engine.h"

namespace eng
{
	MeshComponent::MeshComponent(const shared<Material>& material, const shared<Mesh>& mesh) noexcept
		: m_Material{ material },
		m_Mesh{ mesh }
	{

	}

	void MeshComponent::LoadPropertiesFromJson(const nlohmann::json& json)
	{
		// loading material
		if (json.contains("material"))
		{
			auto& matObj = json["material"];
			const std::string path = matObj.value("path", "");
			auto mat = Material::LoadFromJson(path);
			if (mat && matObj.contains("params"))
			{
				auto& paramsObj = matObj["params"];

				// Float1
				if (paramsObj.contains("float"))
				{
					for (auto& p : paramsObj["float"])
					{
						std::string name = p.value("name", "");
						float value = p.value("value", 0.0f);
						mat->SetFloatParam(name, value);
					}
				}

				// Float2
				if (paramsObj.contains("float2"))
				{
					for (auto& p : paramsObj["float2"])
					{
						std::string name = p.value("name", "");
						float v0 = p.value("value0", 0.0f);
						float v1 = p.value("value1", 0.0f);
						mat->SetFloatParam(name, v0, v1);
					}
				}

				// Float3
				if (paramsObj.contains("float3"))
				{
					for (auto& p : paramsObj["float3"])
					{
						std::string name = p.value("name", "");
						float v0 = p.value("value0", 0.0f);
						float v1 = p.value("value1", 0.0f);
						float v2 = p.value("value2", 0.0f);
						mat->SetFloatParam(name, glm::vec3(v0, v1, v2));
					}
				}

				// Textures
				if (paramsObj.contains("textures"))
				{
					for (auto& p : paramsObj["textures"])
					{
						std::string name = p.value("name", "");
						std::string texPath = p.value("path", "");
						auto texture = Texture::Load(texPath);

						mat->SetTextureParam(name, texture);
					}
				}
			}

			//const std::string matPath = json.value("material", "");
			//auto material = Material::Load(matPath);
			//if (material)
			//{
			//	SetMaterial(material);
			//}
			SetMaterial(mat);
		}

		// loading mesh
		if (json.contains("mesh"))
		{
			const auto& meshObj = json["mesh"];
			const std::string type = meshObj.value("type", "box");
			if (type == "box")
			{
				glm::vec3 extents(
					meshObj.value("x", 1.0f),
					meshObj.value("y", 1.0f),
					meshObj.value("z", 1.0f)
				);
				auto mesh = Mesh::CreateBox(extents);
				SetMesh(mesh);
			}
			else if (type == "sphere")
			{
				float r = meshObj.value("r", 1.0f);
				auto mesh = Mesh::CreateSphere(r, 16, 16);
				SetMesh(mesh);
			}
			else if (type == "cone")
			{
				float radius = meshObj.value("r", 0.5f);
				float height = meshObj.value("h", 1.0f);
				auto mesh = Mesh::CreateCone(
					radius, height, 32);
				SetMesh(mesh);
			}
			else if (type == "cylinder")
			{
				float radius = meshObj.value("r", 0.5f);
				float height = meshObj.value("h", 1.0f);
				auto mesh = Mesh::CreateCylinder(
					radius, height, 32);
				SetMesh(mesh);
			}
		}
	}

	void MeshComponent::LoadPropertiesFromLua(const sol::table& table)
	{
		// loading material
		if (LuaLoaderUtil::LuaHasKey(table, "material"))
		{
			sol::object matObjRaw = table.get<sol::object>("material");
			if (LuaLoaderUtil::LuaIsTable(matObjRaw))
			{
				sol::table matObj = matObjRaw.as<sol::table>();
				const std::string path = LuaLoaderUtil::LuaValueOrStr(matObj, "path", "");
				auto mat = Material::LoadFromJson(path);

				if (mat && LuaLoaderUtil::LuaHasKey(matObj, "params"))
				{
					sol::object paramsObjRaw = matObj.get<sol::object>("params");
					if (LuaLoaderUtil::LuaIsTable(paramsObjRaw))
					{
						sol::table paramsObj = paramsObjRaw.as<sol::table>();

						// Float1
						if (LuaLoaderUtil::LuaHasKey(paramsObj, "float"))
						{
							sol::object floatArrRaw = paramsObj.get<sol::object>("float");
							if (LuaLoaderUtil::LuaIsTable(floatArrRaw))
							{
								sol::table floatArr = floatArrRaw.as<sol::table>();
								for (auto& kv : floatArr)
								{
									if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
									sol::table p = kv.second.as<sol::table>();

									std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
									float value = LuaLoaderUtil::LuaValueOr<float>(p, "value", 0.0f);
									mat->SetFloatParam(name, value);
								}
							}
						}

						// Float2
						if (LuaLoaderUtil::LuaHasKey(paramsObj, "float2"))
						{
							sol::object float2ArrRaw = paramsObj.get<sol::object>("float2");
							if (LuaLoaderUtil::LuaIsTable(float2ArrRaw))
							{
								sol::table float2Arr = float2ArrRaw.as<sol::table>();
								for (auto& kv : float2Arr)
								{
									if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
									sol::table p = kv.second.as<sol::table>();

									std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
									float v0 = LuaLoaderUtil::LuaValueOr<float>(p, "value0", 0.0f);
									float v1 = LuaLoaderUtil::LuaValueOr<float>(p, "value1", 0.0f);
									mat->SetFloatParam(name, v0, v1);
								}
							}
						}

						// Float3
						if (LuaLoaderUtil::LuaHasKey(paramsObj, "float3"))
						{
							sol::object float3ArrRaw = paramsObj.get<sol::object>("float3");
							if (LuaLoaderUtil::LuaIsTable(float3ArrRaw))
							{
								sol::table float3Arr = float3ArrRaw.as<sol::table>();
								for (auto& kv : float3Arr)
								{
									if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
									sol::table p = kv.second.as<sol::table>();

									std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
									float v0 = LuaLoaderUtil::LuaValueOr<float>(p, "value0", 0.0f);
									float v1 = LuaLoaderUtil::LuaValueOr<float>(p, "value1", 0.0f);
									float v2 = LuaLoaderUtil::LuaValueOr<float>(p, "value2", 0.0f);
									mat->SetFloatParam(name, glm::vec3(v0, v1, v2));
								}
							}
						}

						// Textures
						if (LuaLoaderUtil::LuaHasKey(paramsObj, "textures"))
						{
							sol::object texturesArrRaw = paramsObj.get<sol::object>("textures");
							if (LuaLoaderUtil::LuaIsTable(texturesArrRaw))
							{
								sol::table texturesArr = texturesArrRaw.as<sol::table>();
								for (auto& kv : texturesArr)
								{
									if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
									sol::table p = kv.second.as<sol::table>();

									std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
									std::string texPath = LuaLoaderUtil::LuaValueOrStr(p, "path", "");
									auto texture = Texture::Load(texPath);
									mat->SetTextureParam(name, texture);
								}
							}
						}
					}
				}

				SetMaterial(mat);
			}
		}

		// loading mesh
		if (LuaLoaderUtil::LuaHasKey(table, "mesh"))
		{
			sol::object meshObjRaw = table.get<sol::object>("mesh");
			if (LuaLoaderUtil::LuaIsTable(meshObjRaw))
			{
				sol::table meshObj = meshObjRaw.as<sol::table>();
				const std::string type = LuaLoaderUtil::LuaValueOrStr(meshObj, "type", "box");

				if (type == "box")
				{
					glm::vec3 extents(
						LuaLoaderUtil::LuaValueOr<float>(meshObj, "x", 1.0f),
						LuaLoaderUtil::LuaValueOr<float>(meshObj, "y", 1.0f),
						LuaLoaderUtil::LuaValueOr<float>(meshObj, "z", 1.0f)
					);
					auto mesh = Mesh::CreateBox(extents);
					SetMesh(mesh);
				}
				else if (type == "sphere")
				{
					float r = LuaLoaderUtil::LuaValueOr<float>(meshObj, "r", 1.0f);
					auto mesh = Mesh::CreateSphere(r, 16, 16);
					SetMesh(mesh);
				}
				else if (type == "cone")
				{
					float radius = LuaLoaderUtil::LuaValueOr<float>(meshObj, "r", 0.5f);
					float height = LuaLoaderUtil::LuaValueOr<float>(meshObj, "h", 1.0f);
					auto mesh = Mesh::CreateCone(radius, height, 32);
					SetMesh(mesh);
				}
				else if (type == "cylinder")
				{
					float radius = LuaLoaderUtil::LuaValueOr<float>(meshObj, "r", 0.5f);
					float height = LuaLoaderUtil::LuaValueOr<float>(meshObj, "h", 1.0f);
					auto mesh = Mesh::CreateCylinder(radius, height, 32);
					SetMesh(mesh);
				}
			}
		}
	}

	void MeshComponent::Update(float deltaTime)
	{
		if (!m_Material || !m_Mesh) return;

		RenderCommand command;
		command.material = m_Material.get();
		command.mesh = m_Mesh.get();
		command.modelMatrix = GetOwner()->GetWorldTransform();

		// Render Queue to organize the draw calls and submit the command during update
		auto& renderQueue = Engine::GetInstance().GetRenderQueue();
		renderQueue.Submit(command);
	}
}

