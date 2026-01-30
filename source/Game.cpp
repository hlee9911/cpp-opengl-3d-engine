#include "Game.h"
#include "TestObject.h"

bool Game::Init()
{
	m_Scene.CreateGameObject<TestObject>("TestObject");

	return true;
}

void Game::Update(float deltaTime)
{
	m_Scene.Update(deltaTime);
}

void Game::Destroy()
{

}
