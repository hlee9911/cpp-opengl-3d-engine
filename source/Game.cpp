#include "Game.h"

#include <iostream>

#include <GLFW/glfw3.h>

bool Game::Init()
{
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
