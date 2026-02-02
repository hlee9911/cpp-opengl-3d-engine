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

