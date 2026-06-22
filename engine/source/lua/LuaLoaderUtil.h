#pragma once

#include <sol/sol.hpp>
#include <sol/forward.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

#include <string>

namespace eng
{
	// Lua and Sol2 helper util functions for loading the lua formatted scene
	class LuaLoaderUtil
	{
	public:

		// simliar to nlohmann::json::value(key, default)
		template <typename T>
		static T LuaValueOr(const sol::table& t, const char* key, T defaultValue)
		{
			if (!t.valid()) return defaultValue;

			sol::object obj = t.get<sol::object>(key);
			if (!obj.valid() || obj.get_type() == sol::type::lua_nil) return defaultValue;

			sol::optional<T> maybe = obj.as<sol::optional<T>>();
			if (maybe) return *maybe;

			return defaultValue;
		}

		// std::string overload that also accepts numbers to string edge cases gracefully
		// Note: kept separate from LuaValueOr<T> because sol2s generic as<std::string>()
		//		 this will stringify numbers/booleans, which we dont want here
		static std::string LuaValueOrStr(const sol::table& t, const char* key, const std::string& defaultValue);

		static bool LuaHasKey(const sol::table& t, const char* key);

		static bool LuaIsTable(const sol::object& obj);

		// similar to jsonObject["x"]-style vec3 extraction with default fallback
		static glm::vec3 LuaToVec3(const sol::table& t, float defX = 0.0f, float defY = 0.0f, float defZ = 0.0f);

		// similar to jsonObject["x"]-style vec2 extraction with default fallback
		static glm::vec2 LuaToVec2(const sol::table& t, float defX = 0.0f, float defY = 0.0f);

		static glm::quat LuaToQuat(const sol::table& t);
	};
}
