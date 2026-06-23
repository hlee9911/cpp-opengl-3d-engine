#include "scene/components/SpriteComponent.h"
#include "graphics/Texture.h"
#include "render/RenderQueue.h"
#include "scene/GameObject.h"
#include "Engine.h"

#include <string>

namespace eng
{
	void SpriteComponent::LoadPropertiesFromJson(const nlohmann::json& json)
	{
		// Load texture
		const std::string texturePath = json.value("texture", "");

		if (auto texture = Texture::Load(texturePath))
		{
			SetTexture(texture);
		}
		
		// Load color
		if (json.contains("color"))
		{
			auto& colorObj = json["color"];
			glm::vec4 color(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f),
				colorObj.value("a", 1.0f)
			);
			SetColor(color);
		}

		// Load size
		if (json.contains("size"))
		{
			auto& sizeObj = json["size"];
			glm::vec2 size(
				sizeObj.value("x", 100.0f),
				sizeObj.value("y", 100.0f)
			);
			SetSize(size);
		}

		// Load LowerLeftUV
		if (json.contains("lowerLeftUV"))
		{
			auto& uvObj = json["lowerLeftUV"];
			glm::vec2 lowerLeftUV(
				uvObj.value("u", 0.0f),
				uvObj.value("v", 0.0f)
			);
			SetLowerLeftUV(lowerLeftUV);
		}

		// Load UpperRightUV
		if (json.contains("upperRightUV"))
		{
			auto& uvObj = json["upperRightUV"];
			glm::vec2 upperRightUV(
				uvObj.value("u", 1.0f),
				uvObj.value("v", 1.0f)
			);
			SetUpperRightUV(upperRightUV);
		}

		// Load pivot
		if (json.contains("pivot"))
		{
			auto& pivotObj = json["pivot"];
			glm::vec2 pivot(
				pivotObj.value("x", 0.5f),
				pivotObj.value("y", 0.5f)
			);
			SetPivot(pivot);
		}
	}

	void SpriteComponent::LoadPropertiesFromLua(const sol::table& table)
	{
		// Load texture
		const std::string texturePath = LuaLoaderUtil::LuaValueOrStr(table, "texture", "");
		if (auto texture = Texture::Load(texturePath))
		{
			SetTexture(texture);
		}

		// Load color
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

		// Load size
		if (LuaLoaderUtil::LuaHasKey(table, "size"))
		{
			sol::object sizeObjRaw = table.get<sol::object>("size");
			if (LuaLoaderUtil::LuaIsTable(sizeObjRaw))
			{
				sol::table sizeObj = sizeObjRaw.as<sol::table>();
				glm::vec2 size(
					LuaLoaderUtil::LuaValueOr<float>(sizeObj, "x", 100.0f),
					LuaLoaderUtil::LuaValueOr<float>(sizeObj, "y", 100.0f)
				);
				SetSize(size);
			}
		}

		// Load LowerLeftUV
		if (LuaLoaderUtil::LuaHasKey(table, "lowerLeftUV"))
		{
			sol::object uvObjRaw = table.get<sol::object>("lowerLeftUV");
			if (LuaLoaderUtil::LuaIsTable(uvObjRaw))
			{
				sol::table uvObj = uvObjRaw.as<sol::table>();
				glm::vec2 lowerLeftUV(
					LuaLoaderUtil::LuaValueOr<float>(uvObj, "u", 0.0f),
					LuaLoaderUtil::LuaValueOr<float>(uvObj, "v", 0.0f)
				);
				SetLowerLeftUV(lowerLeftUV);
			}
		}

		// Load UpperRightUV
		if (LuaLoaderUtil::LuaHasKey(table, "upperRightUV"))
		{
			sol::object uvObjRaw = table.get<sol::object>("upperRightUV");
			if (LuaLoaderUtil::LuaIsTable(uvObjRaw))
			{
				sol::table uvObj = uvObjRaw.as<sol::table>();
				glm::vec2 upperRightUV(
					LuaLoaderUtil::LuaValueOr<float>(uvObj, "u", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(uvObj, "v", 1.0f)
				);
				SetUpperRightUV(upperRightUV);
			}
		}

		// Load pivot
		if (LuaLoaderUtil::LuaHasKey(table, "pivot"))
		{
			sol::object pivotObjRaw = table.get<sol::object>("pivot");
			if (LuaLoaderUtil::LuaIsTable(pivotObjRaw))
			{
				sol::table pivotObj = pivotObjRaw.as<sol::table>();
				glm::vec2 pivot(
					LuaLoaderUtil::LuaValueOr<float>(pivotObj, "x", 0.5f),
					LuaLoaderUtil::LuaValueOr<float>(pivotObj, "y", 0.5f)
				);
				SetPivot(pivot);
			}
		}
	}

	void SpriteComponent::Update(float deltaTime)
	{
		if (!m_Texture || !m_Visible) return;

		// render queue submission
		RenderCommand2D command;
		command.modelMatrix = GetOwner()->GetWorldTransform2D();
		command.texture = m_Texture.get();
		command.color = m_Color;
		command.size = m_Size;
		command.lowerLeftUV = m_LowerLeftUV;
		command.upperRightUV = m_UpperRightUV;
		command.pivot = m_Pivot;

		auto& renderQueue = Engine::GetInstance().GetRenderQueue();
		renderQueue.Submit(command);
	}

}
