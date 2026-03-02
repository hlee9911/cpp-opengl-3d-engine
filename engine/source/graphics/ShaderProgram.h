#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <string>
#include <unordered_map>

#include "Core.h"

namespace eng
{
	class Texture;

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
		void SetUniform(const std::string& name, float v0, float v1);
		void SetUniform(const std::string& name, const glm::mat4& mat);
		void SetUniform(const std::string& name, const glm::vec3& value);
		void SetTexture(const std::string& name, Texture* texture);

	private:
		Dictionary<std::string, GLint> m_UniformLocationCache;
		GLuint m_ShaderProgramID = 0;
		int m_CurrentTextureUnit = 0;
	};
}
