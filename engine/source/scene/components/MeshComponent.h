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
		virtual void LoadPropertiesFromJson(const nlohmann::json& json) override;
		virtual void LoadPropertiesFromLua(const sol::table& table) override;
		virtual void Update(float deltaTime) override;

		void SetMaterial(const shared<Material>& material) { m_Material = material; }
		void SetMesh(const shared<Mesh>& mesh) { m_Mesh = mesh; }

		const shared<Material>& GetMaterial() const { return m_Material; }
		const shared<Mesh>& GetMesh() const { return m_Mesh; }

	private:
		shared<Material> m_Material;
		shared<Mesh> m_Mesh;
	};
}
