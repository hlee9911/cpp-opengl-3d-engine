#include "Game.h"

#include <iostream>

#include <GLFW/glfw3.h>

bool Game::Init()
{
	std::string vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;

		out vec3 vColor;

        void main()
        {
			vColor = color;
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
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

	return true;
}

void Game::Update(float deltaTime)
{
	// std::cout << "Current Delta Time: " << deltaTime << " seconds" << std::endl;
	auto& input = eng::Engine::GetInstance().GetInputManager();

	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		std::cout << "W key is pressed." << std::endl;
	}
}

void Game::Destroy()
{

}
