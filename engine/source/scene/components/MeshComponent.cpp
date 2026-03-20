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

	void MeshComponent::LoadProperties(const nlohmann::json& json)
	{
		// loading material
		if (json.contains("material"))
		{
			const std::string matPath = json.value("material", "");
			auto material = Material::Load(matPath);
			if (material)
			{
				SetMaterial(material);
			}
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

