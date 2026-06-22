#include "lua/LuaLoaderUtil.h"

namespace eng
{
	std::string LuaLoaderUtil::LuaValueOrStr(const sol::table& t, const char* key, const std::string& defaultValue)
	{
		if (!t.valid()) return defaultValue;

		sol::object obj = t.get<sol::object>(key);
		if (!obj.valid() || obj.get_type() == sol::type::lua_nil) return defaultValue;

		if (obj.get_type() == sol::type::string) return obj.as<std::string>();

		return defaultValue;
	}

	bool LuaLoaderUtil::LuaHasKey(const sol::table& t, const char* key)
	{
		if (!t.valid()) return false;

		sol::object obj = t.get<sol::object>(key);
		return obj.valid() && obj.get_type() != sol::type::lua_nil;
	}

	bool LuaLoaderUtil::LuaIsTable(const sol::object& obj)
	{
		return obj.valid() && obj.get_type() == sol::type::table;
	}

	glm::vec3 LuaLoaderUtil::LuaToVec3(const sol::table & t, float defX, float defY, float defZ)
	{
		glm::vec3 v;
		v.x = LuaValueOr<float>(t, "x", defX);
		v.y = LuaValueOr<float>(t, "y", defY);
		v.z = LuaValueOr<float>(t, "z", defZ);
		return v;
	}

	glm::vec2 LuaLoaderUtil::LuaToVec2(const sol::table& t, float defX, float defY)
	{
		glm::vec2 v;
		v.x = LuaValueOr<float>(t, "x", defX);
		v.y = LuaValueOr<float>(t, "y", defY);
		return v;
	}

	glm::quat LuaLoaderUtil::LuaToQuat(const sol::table& t)
	{
		glm::quat q;
		q.x = LuaValueOr<float>(t, "x", 0.0f);
		q.y = LuaValueOr<float>(t, "y", 0.0f);
		q.z = LuaValueOr<float>(t, "z", 0.0f);
		q.w = LuaValueOr<float>(t, "w", 1.0f);
		return q;
	}

}
