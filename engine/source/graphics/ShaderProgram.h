#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>

#include <string>
#include <unordered_map>

namespace eng
{
	class ShaderProgram
	{
	public:
		// delete default constructor and copy operations
		// this is to avoid double deletion of the same OpenGL resource
		ShaderProgram() noexcept = default;
		ShaderProgram(const ShaderProgram&) noexcept = delete;
		ShaderProgram& operator=(const ShaderProgram&) noexcept = delete;

		explicit ShaderProgram(GLuint shaderProgramID) noexcept;
		~ShaderProgram() noexcept;

		void Bind();
		GLint GetUniformLocation(const std::string& name);
		void SetUniform(const std::string& name, float value);

	private:
		std::unordered_map<std::string, GLint> m_UniformLocationCache;
		GLuint m_ShaderProgramID = 0;
	};
}

#endif // SHADERPROGRAM_H
