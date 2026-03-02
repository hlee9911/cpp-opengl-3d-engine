#pragma once

#include "Core.h"
#include "scene/Component.h"

#include <glm/vec3.hpp>

namespace eng
{
	class LightComponent : public Component
	{
		COMPONENT(LightComponent)

	public:
		void Update(float deltaTime) override;

		void SetColor(const glm::vec3& color) noexcept { m_Color = color; }
		const glm::vec3& GetColor() const noexcept { return m_Color; }

	private:
		glm::vec3 m_Color = glm::vec3(1.0f);
	};
}
