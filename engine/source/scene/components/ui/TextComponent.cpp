#include "scene/components/ui/TextComponent.h"
#include "font/Font.h"
#include "Engine.h"

namespace eng
{
	void TextComponent::LoadProperties(const nlohmann::json& json)
	{
		const std::string text = json.value("text", "");
		SetText(text);

		if (json.contains("font"))
		{
			const auto& fontObj = json["font"];
			std::string& path = fontObj.value("path", "");

			int fontSize = fontObj.value("size", 12);
			SetFont(path, fontSize);
		}

		if (json.contains("color"))
		{
			const auto& colorObj = json["color"];
			glm::vec4 color(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f),
				colorObj.value("a", 1.0f)
			);
			SetColor(color);
		}
	}

	void TextComponent::Render(CanvasComponent* canvas)
	{
		if (m_Text.empty() || !m_Font || !canvas) return;

		// TODO: starting drawing the text
	}

	void TextComponent::SetFont(const std::string& path, int size)
	{
		m_Font = Engine::GetInstance().GetFontManager().GetFont(path, size);
	}

	const glm::vec2 TextComponent::GetPivotPos() const
	{
		auto pos = m_Owner->GetWorldPosition2D();

		glm::vec2 rect(0.0f);
		for (const auto c : m_Text)
		{
			// get description from the text
			const auto& d = m_Font->GetGlyphDescription(c);
			rect.x += static_cast<float>(d.advance);
			rect.y = std::max(rect.y, static_cast<float>(d.height));
		}

		pos.x -= std::round(rect.x * m_Pivot.x);
		pos.y -= std::round(rect.y * m_Pivot.y);
		return pos;
	}
}
