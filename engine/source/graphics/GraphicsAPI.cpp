#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include "render/Material.h"
#include "render/Mesh.h"

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
		ShaderKey key{ vertexSource, fragmentSource };
		auto it = m_ShaderCache.find(key);
		if (it != m_ShaderCache.end())
		{
			return it->second; // Return the cached shader program if it exists
		}

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
			Logger::Error("VERTEX_SHADER_COMPILATION_FAILED: " + std::string(infoLog));
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
			Logger::Error("FRAGMENT_SHADER_COMPILATION_FAILED: " + std::string(infoLog));
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
			Logger::Error("SHADER_PROGRAM_LINKING_FAILED: " + std::string(infoLog));
			return nullptr;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		auto shaderProgram = std::make_shared<ShaderProgram>(shaderProgramID);
		m_ShaderCache.emplace(key, shaderProgram);

		return shaderProgram;
	}

	const shared<ShaderProgram>& GraphicsAPI::GetDefaultShaderProgram()
	{
		if (!m_DefaultShaderProgram)
		{
			std::string vertexShaderSource = R"(
				#version 460 core
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

					vNormal = normalize(transpose(inverse(mat3(uModel))) * normal);
					
					vFragPos = vec3(uModel * vec4(position, 1.0));

					gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
				}
			)";

			std::string fragmentShaderSource = R"(
				#version 460 core
				
				struct Light
				{
					vec3 color;
					vec3 direction;
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

					// diffuse lighting for basic shading
					vec3 lightDir = normalize(-uLight.direction);
					float diff = max(dot(norm, lightDir), 0.0);
					vec3 diffuse = diff * uLight.color;

					// specular lighting for shiny highlights
					vec3 viewDir = normalize(uCameraPos - vFragPos);
					vec3 reflectDir = reflect(-lightDir, norm);
					float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // dot(viewDir, reflectDir) measures how much the view direction aligns with the reflection direction, raised to a power for shininess
					float specularStrength = 0.5;
					vec3 specular = specularStrength * spec * uLight.color;

					// create ambient lighting to ensure the object is visible even without direct light
					const float ambientStrength = 0.4;
					vec3 ambient = ambientStrength * uLight.color;
    
					vec3 result = diffuse + specular + ambient;

					vec4 texColor = texture(baseColorTexture, vUV);

					FragColor = texColor * vec4(result, 1.0);
				}

			)";

			m_DefaultShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		return m_DefaultShaderProgram;
	}

	const shared<ShaderProgram>& GraphicsAPI::GetDefault2DShaderProgram()
	{
		if (!m_Default2DShaderProgram)
		{
			std::string vertexShaderSource = R"(
				#version 460 core
				layout(location = 0) in vec2 position;

				out vec2 vUV;

				uniform mat4 uModel;
				uniform mat4 uView;
				uniform mat4 uProjection;

				uniform vec2 uPivot;
				uniform vec2 uSize;

				uniform vec2 uUVMin;
				uniform vec2 uUVMax;

				void main()
				{
					// apply pivot and size transformations to the vertex position
					vec2 local = (position - uPivot) * uSize;
					vUV = mix(uUVMin, uUVMax, position);

					gl_Position = uProjection * uView * uModel * vec4(local, 0.0, 1.0);
				}
			)";

			std::string fragmentShaderSource = R"(
				#version 460 core

				in vec2 vUV;

				uniform vec4 uColor;

				uniform sampler2D uTex;

				out vec4 FragColor;

				void main()
				{
					// texture color is tinted by the uniform color, allowing for easy color modulation of sprites
					vec4 src = texture(uTex, vUV) * uColor;
					FragColor = src;
				}

			)";

			m_Default2DShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		return m_Default2DShaderProgram;
	}

	const shared<ShaderProgram>& GraphicsAPI::GetDefaultUIShaderProgram()
	{
		if (!m_DefaultUIShaderProgram)
		{
			std::string vertexShaderSource = R"(
				#version 460 core
				layout(location = 0) in vec2 position;
				layout(location = 1) in vec4 color;
				layout(location = 2) in vec2 uv;

				out vec2 vUV;
				out vec4 vColor;

				uniform mat4 uProjection;

				void main()
				{
					vUV = uv;
					vColor = color;

					gl_Position = uProjection * vec4(position, 0.0, 1.0);
				}
			)";

			// sample uTex or output flat vColor
			std::string fragmentShaderSource = R"(
				#version 460 core

				in vec2 vUV;
				in vec4 vColor;

				uniform sampler2D uTex;
				uniform int uUseTexture;

				out vec4 FragColor;

				void main()
				{
					vec4 src = (uUseTexture != 0) ? texture(uTex, vUV) * vColor : vColor;
					FragColor = src;
				}

			)";

			m_DefaultUIShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		return m_DefaultUIShaderProgram;
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

	const Rect& GraphicsAPI::GetViewport() const
	{
		return m_Viewport;
	}

	void GraphicsAPI::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
		m_Viewport.x = x;
		m_Viewport.y = y;
		m_Viewport.width = width;
		m_Viewport.height = height;
	}

	void GraphicsAPI::SetDepthTestEnabled(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}

	void GraphicsAPI::SetBlendMode(BlendMode mode)
	{
		switch (mode)
		{
			case BlendMode::Disabled:
				{
					glDisable(GL_BLEND);
				}
				break;
			case BlendMode::Alpha:
				{
					glEnable(GL_BLEND);
					// alpha uses source alpha weighting
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
				break;
			case BlendMode::Additive: // additive ignores alpha and brightness
				{
					glEnable(GL_BLEND);
					glBlendFunc(GL_ONE, GL_ONE);
				}
				break;
			case BlendMode::Multiply:
				{
					glEnable(GL_BLEND);
					glBlendFunc(GL_DST_COLOR, GL_ZERO);
				}	
				break;
			default:
				{
					glDisable(GL_BLEND);
				}
				break;
		}
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

	void GraphicsAPI::UnbindMesh(Mesh* mesh)
	{
		if (!mesh) return;
		mesh->Unbind();
	}

	void GraphicsAPI::DrawMesh(Mesh* mesh)
	{
		if (!mesh) return;
		mesh->Draw();
	}
}
