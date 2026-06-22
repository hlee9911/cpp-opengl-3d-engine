#include "scene/components/LightComponent.h"

namespace eng
{
	void LightComponent::LoadPropertiesFromJson(const nlohmann::json& json)
	{
		if (json.contains("color"))
		{
			const auto& colorObj = json["color"];
			glm::vec3 color(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f)
			);
			SetColor(color);
		}
	}

	void LightComponent::LoadPropertiesFromLua(const sol::table& table)
	{
		if (LuaLoaderUtil::LuaHasKey(table, "color"))
		{
			sol::object colorObjRaw = table.get<sol::object>("color");
			if (LuaLoaderUtil::LuaIsTable(colorObjRaw))
			{
				sol::table colorObj = colorObjRaw.as<sol::table>();
				glm::vec3 color(
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "r", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "g", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(colorObj, "b", 1.0f)
				);
				SetColor(color);
			}
		}
	}

	void LightComponent::Update(float deltaTime)
	{

	}
};

