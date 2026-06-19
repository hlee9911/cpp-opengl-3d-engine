#pragma once

#include "scene/components/ui/UIElementComponent.h"
#include "Core.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>

namespace eng
{
	class Font;

	class TextComponent : public UIElementComponent
	{
		COMPONENT_WITH_PARENT(TextComponent, UIElementComponent)

	public:
		void LoadPropertiesFromJson(const nlohmann::json& json) override;
		void Render(CanvasComponent* canvas) override;

		void SetText(const std::string& text) noexcept { m_Text = text; }
		const std::string& GetText() const noexcept { return m_Text; }
		
		void SetColor(const glm::vec4& color) noexcept { m_Color = color; }
		const glm::vec4& GetColor() const noexcept { return m_Color; }

		void SetFont(const shared<Font>& font) noexcept { m_Font = font; }
		void SetFont(const std::string& path, int size);
		const shared<Font>& GetFont() const noexcept { return m_Font; }

		const glm::vec2 GetPivotPos();

	private:
		std::string m_Text;
		glm::vec4 m_Color = glm::vec4(1.0f);
		shared<Font> m_Font;
	};
}