#include "render/Material.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "Engine.h"

#include <nlohmann/json.hpp>

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

	void Material::SetTextureParam(const std::string& name, const shared<Texture>& texture)
	{
		m_Textures[name] = texture;
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

		for (auto& param : m_Textures)
		{
			m_ShaderProgram->SetTexture(param.first, param.second.get());
		}
	}

	/// <summary>
	/// Load the material file that is in a json format and creates the material 
	/// and sets the parameter values accordingly
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	shared<Material> Material::Load(const std::string& path)
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
}
