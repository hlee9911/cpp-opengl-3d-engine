#include "render/Material.h"
#include "graphics/ShaderProgram.h"

namespace eng
{
	void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) noexcept
	{
		m_ShaderProgram = shaderProgram;
	}

	void Material::SetFloatParam(const std::string& name, float value) noexcept
	{
		m_FloatParams[name] = value;
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
	}
}
