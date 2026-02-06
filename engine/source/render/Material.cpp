#include "render/Material.h"
#include "graphics/ShaderProgram.h"

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
	}
}
