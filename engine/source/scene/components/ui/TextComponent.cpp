#include "scene/components/ui/TextComponent.h"
#include "scene/components/ui/CanvasComponent.h"
#include "scene/components/ui/RectTransformComponent.h"
#include "font/Font.h"
#include "Engine.h"

namespace eng
{
	void TextComponent::LoadPropertiesFromJson(const nlohmann::json& json)
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

	void TextComponent::LoadPropertiesFromLua(const sol::table& table)
	{
		const std::string text = LuaLoaderUtil::LuaValueOrStr(table, "text", "");
		SetText(text);

		if (LuaLoaderUtil::LuaHasKey(table, "font"))
		{
			sol::object fontObjRaw = table.get<sol::object>("font");
			if (LuaLoaderUtil::LuaIsTable(fontObjRaw))
			{
				sol::table fontObj = fontObjRaw.as<sol::table>();
				std::string path = LuaLoaderUtil::LuaValueOrStr(fontObj, "path", "");
				int fontSize = LuaLoaderUtil::LuaValueOr<int>(fontObj, "size", 12);
				SetFont(path, fontSize);
			}
		}

		if (LuaLoaderUtil::LuaHasKey(table, "color"))
		{
			sol::object colorObjRaw = table.get<sol::object>("color");
			if (LuaLoaderUtil::LuaIsTable(colorObjRaw))
			{
				sol::table colorObj = colorObjRaw.as<sol::table>();
				glm::vec4 color(
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "r", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "g", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "b", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "a", 1.0f)
				);
				SetColor(color);
			}
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

	const glm::vec2 TextComponent::GetPivotPos()
	{
		auto rt = GetOwner()->GetComponent<RectTransformComponent>();
		auto pos = rt ? rt->GetScreenPosition() : GetOwner()->GetWorldPosition2D();

		glm::vec2 rect(0.0f);
		for (const auto c : m_Text)
		{
			// get description from the text
			const auto& d = m_Font->GetGlyphDescription(c);
			rect.x += static_cast<float>(d.advance);
			rect.y = std::max(rect.y, static_cast<float>(d.height));
		}

		if (rt)
		{
			pos -= rect * rt->GetPivot();
		}

		pos.x = std::round(pos.x);
		pos.y = std::round(pos.y);
		return pos;
	}
}
