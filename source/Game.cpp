#include "Game.h"
#include "TestObject.h"

bool Game::Init()
{
	m_Scene = new eng::Scene();

	auto camera = m_Scene->CreateGameObject("Camera");
	camera->AddComponenet(new eng::CameraComponent());
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera->AddComponenet(new eng::PlayerControllerComponent());

	m_Scene->SetMainCamera(camera);

	m_Scene->CreateGameObject<TestObject>("TestObject");

	eng::Engine::GetInstance().SetScene(m_Scene);

	return true;
}

void Game::Update(float deltaTime)
{
	m_Scene->Update(deltaTime);
}

void Game::Destroy()
{
	//delete m_Scene;
	//m_Scene = nullptr;
}
