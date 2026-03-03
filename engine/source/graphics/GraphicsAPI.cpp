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
			ERROR("VERTEX_SHADER_COMPILATION_FAILED: \n%s", infoLog);
			// std::cerr << "ERROR::VERTEX_SHADER_COMPILATION_FAILED: \n" << infoLog << std::endl;
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
			ERROR("FRAGMENT_SHADER_COMPILATION_FAILED: \n%s", infoLog);
			// std::cerr << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED: \n" << infoLog << std::endl;
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
			ERROR("SHADER_PROGRAM_LINKING_FAILED: \n%s", infoLog);
			// std::cerr << "ERROR::SHADER_PROGRAM_LINKING_FAILED: \n" << infoLog << std::endl;
			return nullptr;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return std::make_shared<ShaderProgram>(shaderProgramID);
	}

	const shared<ShaderProgram>& GraphicsAPI::GetDefaultShaderProgram()
	{
		if (!m_DefaultShaderProgram)
		{
			std::string vertexShaderSource = R"(
				#version 330 core
				layout(location = 0) in vec3 position;
				layout(location = 1) in vec3 color;
				layout(location = 2) in vec2 uv;
				layout(location = 3) in vec3 normal;

				out vec2 vUV;
				out vec3 vNormal;
				out vec3 vFragPos;

				uniform mat4 uModel;
				uniform mat4 uView;
				uniform mat4 uProjection;

				void main()
				{
					vUV = uv;

					vFragPos = vec3(uModel * vec4(position, 1.0));

					vNormal = mat3(transpose(inverse(uModel))) * normal;

					gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
				}
			)";

			std::string fragmentShaderSource = R"(
				#version 330 core
				
				struct Light
				{
					vec3 color;
					vec3 position;
				};

				uniform Light uLight;
				uniform vec3 uCameraPos;

				out vec4 FragColor;

				in vec2 vUV;
				in vec3 vNormal;
				in vec3 vFragPos;

				uniform sampler2D baseColorTexture;

				void main()
				{
					vec3 norm = normalize(vNormal);

					// diffuse lighting
					vec3 lightDir = normalize(uLight.position - vFragPos);
					float diff = max(dot(norm, lightDir), 0.0);
					vec3 diffuse = diff * uLight.color;

					// specular lighting
					vec3 viewDir = normalize(uCameraPos - vFragPos);
					vec3 reflectDir = reflect(-lightDir, norm);
					float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // dot(viewDir, reflectDir) measures how much the view direction aligns with the reflection direction, raised to a power for shininess
					float specularStrength = 0.5;
					vec3 specular = specularStrength * spec * uLight.color;

					vec3 result = diffuse + specular;

					vec4 texColor = texture(baseColorTexture, vUV);
					FragColor = texColor * vec4(result, 1.0);
				}

			)";

			m_DefaultShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		return m_DefaultShaderProgram;
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
