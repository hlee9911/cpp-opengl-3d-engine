#pragma once
#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "Core.h"
#include "scene/Component.h"

namespace eng
{
	class Material;
	class Mesh;

	class MeshComponent : public Component
	{
	public:
		MeshComponent(const shared<Material>& material, const shared<Mesh>& mesh) noexcept;
		void Update(float deltaTime) override;

	private:
		shared<Material> m_Material;
		shared<Mesh> m_Mesh;
	};
}

#endif //MESHCOMPONENT_H
