#pragma once

#include "Core.h"
#include "scene/Component.h"

namespace eng
{
	class Material;
	class Mesh;

	class MeshComponent : public Component
	{
		COMPONENT(MeshComponent)

	public:
		MeshComponent() noexcept = default;
		MeshComponent(const shared<Material>& material, const shared<Mesh>& mesh) noexcept;
		void LoadProperties(const nlohmann::json& json) override;
		void Update(float deltaTime) override;

		void SetMaterial(const shared<Material>& material) noexcept { m_Material = material; }
		void SetMesh(const shared<Mesh>& mesh) noexcept { m_Mesh = mesh; }

	private:
		shared<Material> m_Material;
		shared<Mesh> m_Mesh;
	};
}
