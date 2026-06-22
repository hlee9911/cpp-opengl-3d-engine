#pragma once

#include "scene/components/ui/UIElementComponent.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <functional>

namespace eng
{
	class ButtonComponent : public UIElementComponent
	{
		COMPONENT_WITH_PARENT(ButtonComponent, UIElementComponent)

	public:
		virtual void LoadPropertiesFromJson(const nlohmann::json& json) override;
		virtual void LoadPropertiesFromLua(const sol::table& table) override;
		void Render(CanvasComponent* canvas) override;
		bool HitTest(const glm::vec2& pos) override;
		void OnPointerEnter() override;
		void OnPointerExit() override;
		void OnPointerUp() override;
		void OnPointerDown() override;
		void OnPointerClick() override;

		//void SetRect(const glm::vec2& rect) noexcept { m_Rect = rect; }
		//const glm::vec2& GetRect() const noexcept { return m_Rect; }

		void SetColor(const glm::vec4& color) noexcept { m_Color = color; }
		const glm::vec4& GetColor() const noexcept { return m_Color; }

		void SetHoveredColor(const glm::vec4& color) noexcept { m_HoveredColor = color; }
		const glm::vec4& GetHoveredColor() const noexcept { return m_HoveredColor; }

		void SetPressedColor(const glm::vec4& color) noexcept { m_PressedColor = color; }
		const glm::vec4& GetPressedColor() const noexcept { return m_PressedColor; }

		std::function<void()> onClick;

	private:
		// glm::vec2 m_Rect = glm::vec2(1.0f);
		glm::vec4 m_Color = glm::vec4(1.0f);
		glm::vec4 m_HoveredColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		glm::vec4 m_PressedColor = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
		glm::vec4* m_CurrentColor = &m_Color;
	};
}
