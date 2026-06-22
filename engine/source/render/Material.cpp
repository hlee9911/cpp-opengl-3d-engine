#include "render/Material.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "Engine.h"

#include <nlohmann/json.hpp>
#include <sol/sol.hpp>

namespace eng
{
	ShaderProgram* Material::GetShaderProgram() noexcept
	{
		return m_ShaderProgram.get();
	}

	void Material::SetShaderProgram(const shared<ShaderProgram>& shaderProgram) noexcept
	{
		m_ShaderProgram = shaderProgram;
	}

	void Material::SetFloatParam(const std::string& name, float value) noexcept
	{
		m_FloatParams[name] = value;
	}

	void Material::SetFloatParam(const std::string& name, float v0, float v1) noexcept
	{
		m_Float2Params[name] = { v0, v1 };
	}

	void Material::SetFloatParam(const std::string& name, const glm::vec3& value) noexcept
	{
		m_Float3Params[name] = value;
	}

	void Material::SetTextureParam(const std::string& name, const shared<Texture>& texture)
	{
		m_Textures[name] = texture;
	}

	void Material::SetBoolParam(const std::string& name, bool value) noexcept
	{
		m_BoolParams[name] = value;
	}

	const glm::vec3 Material::GetFloat3Params(const std::string& name) const noexcept
	{
		auto result = m_Float3Params.find(name);
		if (result != m_Float3Params.end())
		{
			return result->second;
		}
		return glm::vec3(0.0f);
	}

	/// <summary>
	/// Binds the shader program and sets the float parameters as uniforms.
	/// </summary>
	void Material::Bind()
	{
		if (!m_ShaderProgram) return;

		m_ShaderProgram->Bind();

		for (auto& param : m_FloatParams)
		{
			m_ShaderProgram->SetUniform(param.first, param.second);
		}

		for (auto& param : m_Float2Params)
		{
			m_ShaderProgram->SetUniform(param.first, param.second.first, param.second.second);
		}

		for (auto& param : m_Float3Params)
		{
			m_ShaderProgram->SetUniform(param.first, param.second);
		}

		for (auto& param : m_Textures)
		{
			m_ShaderProgram->SetTexture(param.first, param.second.get());
		}

		for (auto& param : m_BoolParams)
		{
			m_ShaderProgram->SetUniform(param.first, param.second);
		}
	}

	/// <summary>
	/// Load the material file that is in a json format and creates the material 
	/// and sets the parameter values accordingly
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	shared<Material> Material::LoadFromJson(const std::string& path)
	{
		auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);

		if (contents.empty()) return nullptr;

		nlohmann::json json = nlohmann::json::parse(contents);
		shared<Material> result;

		if (json.contains("shader"))
		{
			auto shaderObj = json["shader"];
			std::string vertexPath = shaderObj.value("vertex", "");
			std::string fragmentPath = shaderObj.value("fragment", "");

			auto& fs = Engine::GetInstance().GetFileSystem();
			auto vertexSrc = fs.LoadAssetFileText(vertexPath);
			auto fragmentSrc = fs.LoadAssetFileText(fragmentPath);

			auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();
			auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexSrc, fragmentSrc);
			
			if (!shaderProgram) return nullptr;

			result = std::make_shared<Material>();
			result->SetShaderProgram(shaderProgram);
		}

		if (json.contains("params"))
		{
			auto paramsObj = json["params"];

			// Float1
			if (paramsObj.contains("float"))
			{
				for (auto& p : paramsObj["float"])
				{
					std::string name = p.value("name", "");
					float value = p.value("value", 0.0f);
					result->SetFloatParam(name, value);
				}
			}

			// Float2
			if (paramsObj.contains("float2"))
			{
				for (auto& p : paramsObj["float2"])
				{
					std::string name = p.value("name", "");
					float v0 = p.value("value0", 0.0f);
					float v1 = p.value("value1", 0.0f);
					result->SetFloatParam(name, v0, v1);
				}
			}

			// Float3
			if (paramsObj.contains("float3"))
			{
				for (auto& p : paramsObj["float3"])
				{
					std::string name = p.value("name", "");
					float v0 = p.value("value0", 0.0f);
					float v1 = p.value("value1", 0.0f);
					float v2 = p.value("value2", 0.0f);
					result->SetFloatParam(name, glm::vec3(v0, v1, v2));
				}
			}

			// Textures
			if (paramsObj.contains("textures"))
			{
				for (auto& p : paramsObj["textures"])
				{
					std::string name = p.value("name", "");
					std::string texPath = p.value("path", "");
					auto texture = Texture::Load(texPath);
					result->SetTextureParam(name, texture);
				}
			}
		}

		return result;
	}

	// load the mat(lua-formatted one) file
	shared<Material> Material::LoadFromLua(const sol::table& table)
	{
		shared<Material> result;

		if (LuaLoaderUtil::LuaHasKey(table, "shader"))
		{
			sol::object shaderObjRaw = table.get<sol::object>("shader");
			if (LuaLoaderUtil::LuaIsTable(shaderObjRaw))
			{
				sol::table shaderObj = shaderObjRaw.as<sol::table>();

				std::string vertexPath = LuaLoaderUtil::LuaValueOrStr(shaderObj, "vertex", "");
				std::string fragmentPath = LuaLoaderUtil::LuaValueOrStr(shaderObj, "fragment", "");

				auto& fs = Engine::GetInstance().GetFileSystem();
				auto vertexSrc = fs.LoadAssetFileText(vertexPath);
				auto fragmentSrc = fs.LoadAssetFileText(fragmentPath);

				auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();
				auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexSrc, fragmentSrc);

				if (!shaderProgram) return nullptr;

				result = std::make_shared<Material>();
				result->SetShaderProgram(shaderProgram);
			}
		}

		if (LuaLoaderUtil::LuaHasKey(table, "params"))
		{
			sol::object paramsObjRaw = table.get<sol::object>("params");
			if (!LuaLoaderUtil::LuaIsTable(paramsObjRaw)) return result;

			sol::table paramsObj = paramsObjRaw.as<sol::table>();

			// Float1
			if (LuaLoaderUtil::LuaHasKey(paramsObj, "float"))
			{
				sol::object floatArrRaw = paramsObj.get<sol::object>("float");
				if (LuaLoaderUtil::LuaIsTable(floatArrRaw))
				{
					sol::table floatArr = floatArrRaw.as<sol::table>();
					for (auto& kv : floatArr)
					{
						if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
						sol::table p = kv.second.as<sol::table>();

						std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
						float value = LuaLoaderUtil::LuaValueOr<float>(p, "value", 0.0f);
						result->SetFloatParam(name, value);
					}
				}
			}

			// Float2
			if (LuaLoaderUtil::LuaHasKey(paramsObj, "float2"))
			{
				sol::object float2ArrRaw = paramsObj.get<sol::object>("float2");
				if (LuaLoaderUtil::LuaIsTable(float2ArrRaw))
				{
					sol::table float2Arr = float2ArrRaw.as<sol::table>();
					for (auto& kv : float2Arr)
					{
						if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
						sol::table p = kv.second.as<sol::table>();

						std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
						float v0 = LuaLoaderUtil::LuaValueOr<float>(p, "value0", 0.0f);
						float v1 = LuaLoaderUtil::LuaValueOr<float>(p, "value1", 0.0f);
						result->SetFloatParam(name, v0, v1);
					}
				}
			}

			// Float3
			if (LuaLoaderUtil::LuaHasKey(paramsObj, "float3"))
			{
				sol::object float3ArrRaw = paramsObj.get<sol::object>("float3");
				if (LuaLoaderUtil::LuaIsTable(float3ArrRaw))
				{
					sol::table float3Arr = float3ArrRaw.as<sol::table>();
					for (auto& kv : float3Arr)
					{
						if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
						sol::table p = kv.second.as<sol::table>();

						std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
						float v0 = LuaLoaderUtil::LuaValueOr<float>(p, "value0", 0.0f);
						float v1 = LuaLoaderUtil::LuaValueOr<float>(p, "value1", 0.0f);
						float v2 = LuaLoaderUtil::LuaValueOr<float>(p, "value2", 0.0f);
						result->SetFloatParam(name, glm::vec3(v0, v1, v2));
					}
				}
			}

			// Textures
			if (LuaLoaderUtil::LuaHasKey(paramsObj, "textures"))
			{
				sol::object texturesArrRaw = paramsObj.get<sol::object>("textures");
				if (LuaLoaderUtil::LuaIsTable(texturesArrRaw))
				{
					sol::table texturesArr = texturesArrRaw.as<sol::table>();
					for (auto& kv : texturesArr)
					{
						if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
						sol::table p = kv.second.as<sol::table>();

						std::string name = LuaLoaderUtil::LuaValueOrStr(p, "name", "");
						std::string texPath = LuaLoaderUtil::LuaValueOrStr(p, "path", "");
						auto texture = Texture::Load(texPath);
						result->SetTextureParam(name, texture);
					}
				}
			}
		}

		return result;
	}
}
