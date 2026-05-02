#include "scene/components/ui/TextComponent.h"
#include "scene/components/ui/CanvasComponent.h"
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
		int width = m_Font->GetTexture()->GetWidth();
		int height = m_Font->GetTexture()->GetHeight();

		auto pos = GetPivotPos();
		float xOrigin = pos.x;
		float yOrigin = pos.y;

		for (const auto c : m_Text)
		{
			const auto& desc = m_Font->GetGlyphDescription(c);
			
			float x1 = static_cast<float>(xOrigin);
			float y1 = static_cast<float>(yOrigin - desc.height + desc.yOffset); // improves the vertical alignment of the text by using the yOffset
			float x2 = x1 + static_cast<float>(desc.width);
			float y2 = y1 + static_cast<float>(desc.height);
			
			// uv coordinates
			float u1 = static_cast<float>(desc.x0) / static_cast<float>(width);
			float v1 = static_cast<float>(desc.y0) / static_cast<float>(height);
			float u2 = static_cast<float>(desc.x1) / static_cast<float>(width);
			float v2 = static_cast<float>(desc.y1) / static_cast<float>(height);

			xOrigin += desc.advance;

			// we swap v1 and v2
			// UI often uses a top-left origin. while our world uses bottom left
			// swapping v fixes the atlas sampling orientation
			canvas->DrawRect(
				glm::vec2(x1, y1), glm::vec2(x2, y2),
				glm::vec2(u1, v2), glm::vec2(u2, v1),
				m_Font->GetTexture().get(), m_Color
			);
		}
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
