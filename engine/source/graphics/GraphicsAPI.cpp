#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include "render/Material.h"

#include <iostream>

namespace eng
{
	/// <summary>
	/// This function creates a shader program from vertex and fragment shader source code.
	/// and returns a shared pointer to the created ShaderProgram object.
	/// </summary>
	/// <param name="vertexSource"></param>
	/// <param name="fragmentSource"></param>
	/// <returns></returns>
	std::shared_ptr<ShaderProgram> GraphicsAPI::CreateShaderProgram(
		const std::string& vertexSource, 
		const std::string& fragmentSource)
	{
		/////////// vertex shader //////////

		// create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// convert std::string to const char*
		const char* vertexShaderCStr = vertexSource.c_str();
		// tell OpenGL about the shader source code
		glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
		// compile the shader
		glCompileShader(vertexShader);


		// check for compilation errors
		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cerr << "ERROR::VERTEX_SHADER_COMPILATION_FAILED: \n" << infoLog << std::endl;
			return nullptr;
		}

		////////// fragment shader //////////

		// create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		// convert std::string to const char*
		const char* fragmentShaderCStr = fragmentSource.c_str();
		// tell OpenGL about the shader source code
		glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
		// compile the shader
		glCompileShader(fragmentShader);

		// check for compilation errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
			std::cerr << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED: \n" << infoLog << std::endl;
			return nullptr;
		}

		////////// create shader program //////////

		GLuint shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShader);
		glAttachShader(shaderProgramID, fragmentShader);
		glLinkProgram(shaderProgramID);

		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
			std::cerr << "ERROR::SHADER_PROGRAM_LINKING_FAILED: \n" << infoLog << std::endl;
			return nullptr;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return std::make_shared<ShaderProgram>(shaderProgramID);
	}

	/// <summary>
	/// This function binds the given shader program for use in rendering.
	/// </summary>
	/// <param name="shaderProgram"></param>
	void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram)
	{
		if (!shaderProgram) return;
		shaderProgram->Bind();
	}

	void GraphicsAPI::BindMaterial(Material* material)
	{
		if (!material) return;
		material->Bind();
	}
}