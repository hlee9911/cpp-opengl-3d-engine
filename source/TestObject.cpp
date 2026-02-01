#include "TestObject.h"

#include <iostream>
#include <GLFW/glfw3.h>

TestObject::TestObject() noexcept
{
	std::string vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;

		out vec3 vColor;

		uniform mat4 uModel;

        void main()
        {
			vColor = color;
            gl_Position = uModel * vec4(position, 1.0);
        }
    )";

	std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

		in vec3 vColor;
        
        void main()
        {
            FragColor = vec4(vColor, 1.0);
        }
    )";

	auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
	auto shaderProgram = graphicsAPI.CreateShaderProgram(
		vertexShaderSource, fragmentShaderSource);
	m_Material.SetShaderProgram(shaderProgram); // set the shader program to the material, and its ready for rendering

	std::vector<float> verticies =
	{
		// positions        // colors
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
	};

	std::vector<unsigned int> indicies =
	{
		0, 1, 2,
		0, 2, 3
	};

	eng::VertexLayout vertexLayout;

	// Position
	vertexLayout.elements.push_back({
		0, 3, GL_FLOAT, 0 // index, size, type, offset
		});
	// Color
	vertexLayout.elements.push_back({
		1, 3, GL_FLOAT, sizeof(float) * 3 // index, size, type, offset
		});
	// Stride
	vertexLayout.stride = sizeof(float) * 6; // 3 position + 3 color

	// Create mesh 
	m_Mesh = std::make_shared<eng::Mesh>(
		vertexLayout,
		verticies,
		indicies
	);
}

void TestObject::Update(float deltaTime)
{
	eng::GameObject::Update(deltaTime);

	auto position = GetPosition();
	auto& input = eng::Engine::GetInstance().GetInputManager();

	// horizontal movement
	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		position.x -= 0.5f * deltaTime;
	}
	else if (input.IsKeyPressed(GLFW_KEY_D))
	{
		position.x += 0.5f * deltaTime;
	}

	// vertical movement
	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		position.y += 0.5f * deltaTime;
	}
	else if (input.IsKeyPressed(GLFW_KEY_S))
	{
		position.y -= 0.5f * deltaTime;
	}
	SetPosition(position);

	eng::RenderCommand command;
	command.material = &m_Material;
	command.mesh = m_Mesh.get();
	command.modelMatrix = GetWorldTransform();

	// Render Queue to organize the draw calls and submit the command during update
	auto& renderQueue = eng::Engine::GetInstance().GetRenderQueue();
	renderQueue.Submit(command);
}
