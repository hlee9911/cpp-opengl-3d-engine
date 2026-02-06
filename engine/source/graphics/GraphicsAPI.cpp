#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include "render/Material.h"
#include "render/Mesh.h"

#include <iostream>

namespace eng
{
	bool GraphicsAPI::Init()
	{
		// enable the z buffer
		glEnable(GL_DEPTH_TEST);

		return true;
	}

	/// <summary>
	/// This function creates a shader program from vertex and fragment shader source code.
	/// and returns a shared pointer to the created ShaderProgram object.
	/// </summary>
	/// <param name="vertexSource"></param>
	/// <param name="fragmentSource"></param>
	/// <returns></returns>
	shared<ShaderProgram> GraphicsAPI::CreateShaderProgram(
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

	GLuint GraphicsAPI::CreateVertexBuffer(const std::vector<float>& verticies)
	{
		GLuint VBO = 0;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 
			verticies.size() * sizeof(float), 
			verticies.data(), 
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return VBO;
	}

	GLuint GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t>& indicies)
	{
		GLuint EBO = 0;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indicies.size() * sizeof(uint32_t),
			indicies.data(),
			GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return EBO;
	}

	void GraphicsAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void GraphicsAPI::ClearBuffers()
	{
		// need to clear the color buffer and the depth buffer as well
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	void GraphicsAPI::BindMesh(Mesh* mesh)
	{
		if (!mesh) return;
		mesh->Bind();
	}

	void GraphicsAPI::DrawMesh(Mesh* mesh)
	{
		if (!mesh) return;
		mesh->Draw();
	}
}