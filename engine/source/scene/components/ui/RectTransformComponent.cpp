#include "scene/components/ui/RectTransformComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void RectTransformComponent::LoadPropertiesFromJson(const nlohmann::json& json)
	{
		// load size
		if (json.contains("size"))
		{
			auto& sizeObj = json["size"];
			SetSize(glm::vec2(
				sizeObj.value("x", 1.0f), 
				sizeObj.value("y", 1.0f)
			));
		}

		// load anchor
		if (json.contains("anchor"))
		{
			auto& anchorObj = json["anchor"];
			SetAnchor(glm::vec2(
				anchorObj.value("x", 0.0f), 
				anchorObj.value("y", 0.0f)
			));
		}

		// load pivot
		if (json.contains("pivot"))
		{
			auto& pivotObj = json["pivot"];
			SetPivot(glm::vec2(
				pivotObj.value("x", 0.0f), 
				pivotObj.value("y", 0.0f)
			));
		}
	}

	void RectTransformComponent::LoadPropertiesFromLua(const sol::table& table)
	{
		// load size
		if (LuaLoaderUtil::LuaHasKey(table, "size"))
		{
			sol::object sizeObjRaw = table.get<sol::object>("size");
			if (LuaLoaderUtil::LuaIsTable(sizeObjRaw))
			{
				sol::table sizeObj = sizeObjRaw.as<sol::table>();
				SetSize(glm::vec2(
					LuaLoaderUtil::LuaValueOr<float>(sizeObj, "x", 1.0f),
					LuaLoaderUtil::LuaValueOr<float>(sizeObj, "y", 1.0f)
				));
			}
		}

		// load anchor
		if (LuaLoaderUtil::LuaHasKey(table, "anchor"))
		{
			sol::object anchorObjRaw = table.get<sol::object>("anchor");
			if (LuaLoaderUtil::LuaIsTable(anchorObjRaw))
			{
				sol::table anchorObj = anchorObjRaw.as<sol::table>();
				SetAnchor(glm::vec2(
					LuaLoaderUtil::LuaValueOr<float>(anchorObj, "x", 0.0f),
					LuaLoaderUtil::LuaValueOr<float>(anchorObj, "y", 0.0f)
				));
			}
		}

		// load pivot
		if (LuaLoaderUtil::LuaHasKey(table, "pivot"))
		{
			sol::object pivotObjRaw = table.get<sol::object>("pivot");
			if (LuaLoaderUtil::LuaIsTable(pivotObjRaw))
			{
				sol::table pivotObj = pivotObjRaw.as<sol::table>();
				SetPivot(glm::vec2(
					LuaLoaderUtil::LuaValueOr<float>(pivotObj, "x", 0.0f),
					LuaLoaderUtil::LuaValueOr<float>(pivotObj, "y", 0.0f)
				));
			}
		}
	}

	glm::vec2 RectTransformComponent::GetScreenPosition()
	{
		auto parent = GetOwner()->GetParent();
		if (!parent || !parent->GetComponent<RectTransformComponent>())
		{
			return GetOwner()->GetPosition2D();
		}

		auto rect = parent->GetComponent<RectTransformComponent>();
		glm::vec2 parentAnchorPos = rect->GetScreenPosition() +
			(rect->GetAnchor() - rect->GetPivot()) * rect->GetSize();

		return GetOwner()->GetPosition2D() + parentAnchorPos;
	}


}
