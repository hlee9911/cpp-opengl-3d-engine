#include "graphics/ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

namespace eng
{
	ShaderProgram::ShaderProgram(GLuint shaderProgramID) noexcept :
		m_ShaderProgramID(shaderProgramID)
	{

	}

	ShaderProgram::~ShaderProgram() noexcept
	{
		glDeleteProgram(m_ShaderProgramID);
	}

	void ShaderProgram::Bind()
	{
		glUseProgram(m_ShaderProgramID);
	}

	/// <summary>
	/// Gets the location of a uniform variable in the shader program.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	GLint eng::ShaderProgram::GetUniformLocation(const std::string& name)
	{
		auto it = m_UniformLocationCache.find(name);
		if (it != m_UniformLocationCache.end())
		{
			return it->second;
		}
		GLint location = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		m_UniformLocationCache[name] = location;
		return location;
	}

	/// <summary>
	/// Sets the value of a float uniform variable in the shader program.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void ShaderProgram::SetUniform(const std::string& name, float value)
	{
		auto location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void ShaderProgram::SetUniform(const std::string& name, float v0, float v1)
	{
		auto location = GetUniformLocation(name);
		glUniform2f(location, v0, v1);
	}

	void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& mat)
	{
		auto location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
}