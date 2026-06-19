#pragma once

#include "scene/Component.h"

#include <glm/vec2.hpp>

namespace eng
{
	class RectTransformComponent : public Component
	{
		COMPONENT(RectTransformComponent)

	public:
		void LoadPropertiesFromJson(const nlohmann::json& json) override;

		const glm::vec2& GetSize() const noexcept { return m_Size; }
		void SetSize(const glm::vec2& size) noexcept { m_Size = size; }

		const glm::vec2& GetAnchor() const noexcept { return m_Anchor; }
		void SetAnchor(const glm::vec2& anchor) noexcept { m_Anchor = anchor; }

		const glm::vec2& GetPivot() const noexcept { return m_Pivot; }
		void SetPivot(const glm::vec2& pivot) noexcept { m_Pivot = pivot; }

		glm::vec2 GetScreenPosition();

	private:
		glm::vec2 m_Size = glm::vec2(0.0f);
		glm::vec2 m_Anchor = glm::vec2(0.0f);
		glm::vec2 m_Pivot = glm::vec2(0.0f);
	};
}
