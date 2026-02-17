#include "Game.h"
#include "TestObject.h"
#include "Core.h"

bool Game::Init()
{
	auto& fs = eng::Engine::GetInstance().GetFileSystem();
	auto texture = eng::Texture::Load("brick.png");

	m_Scene = new eng::Scene();

	auto camera = m_Scene->CreateGameObject("Camera");
	camera->AddComponenet(new eng::CameraComponent());
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera->AddComponenet(new eng::PlayerControllerComponent());

	m_Scene->SetMainCamera(camera);

	m_Scene->CreateGameObject<TestObject>("TestObject");

	//std::string vertexShaderSource = fs.LoadAssetFileText("shaders/vertex.glsl");
	//std::string fragmentShaderSource = fs.LoadAssetFileText("shaders/fragment.glsl");

	//auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
	//auto shaderProgram = graphicsAPI.CreateShaderProgram(
	//	vertexShaderSource, fragmentShaderSource);

	auto material = eng::Material::Load("materials/brick.mat");
	//material->SetShaderProgram(shaderProgram); // set the shader program to the material, and its ready for rendering
	//material->SetTextureParam("brickTexture", texture);

	//std::vector<float> verticies =
	//{

	//	// Front face
	//	// positions        // colors		    // uvs
	//	0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	-0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,

	//	// Top face
	//	0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	//	-0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	//	 0.5f, 0.5f, 0.5f,  1.0f, 1.0f, 0.0f,   1.0f, 0.0f,

	//	// Right face
	//	0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	//	0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,

	//	// Left face
	//	-0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	//	// Bottom face
	//	0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	//	// Back face
	//	-0.5f, 0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	//	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	//};

	//std::vector<unsigned int> indicies =
	//{
	//	// front face
	//	0, 1, 2,
	//	0, 2, 3,

	//	// top face
	//	4, 5, 6,
	//	4, 6, 7,

	//	// right face
	//	8, 9, 10,
	//	8, 10, 11,

	//	// left face
	//	12, 13, 14,
	//	12, 14, 15,

	//	// bottom face
	//	16, 17, 18,
	//	16, 18, 19,

	//	// back face
	//	20, 21, 22,
	//	20, 22, 23
	//};

	//eng::VertexLayout vertexLayout;

	//// Position
	//vertexLayout.elements.push_back({
	//	0, 
	//	3, 
	//	GL_FLOAT, 
	//	0 // index, size, type, offset
	//});
	//// Color
	//vertexLayout.elements.push_back({
	//	1, 
	//	3, 
	//	GL_FLOAT, 
	//	sizeof(float) * 3 // index, size, type, offset
	//});
	//// UV
	//vertexLayout.elements.push_back({
	//	2,
	//	2,
	//	GL_FLOAT,
	//	sizeof(float) * 6 // index, size, type, offset
	//});

	//// Stride
	//vertexLayout.stride = sizeof(float) * 8; // 3 position + 3 color + 2 uv

	//// Create mesh 
	//auto mesh = std::make_shared<eng::Mesh>(
	//	vertexLayout,
	//	verticies,
	//	indicies
	//);
	
	auto mesh = eng::Mesh::CreateCube();

	auto objectA = m_Scene->CreateGameObject("ObjectA");
	objectA->AddComponenet(new eng::MeshComponent(material, mesh));
	objectA->SetPosition(glm::vec3(1.0f, 0.0f, -5.0f));

	auto objectB = m_Scene->CreateGameObject("ObjectB");
	objectB->AddComponenet(new eng::MeshComponent(material, mesh));
	objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

	auto objectC = m_Scene->CreateGameObject("ObjectC");
	objectC->AddComponenet(new eng::MeshComponent(material, mesh));
	objectC->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
	objectC->SetRotation(glm::vec3(1.0f, 0.0f, 1.0f));
	objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

	auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
	auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

	auto suzanneObj = m_Scene->CreateGameObject("Suzanne");
	suzanneObj->AddComponenet(new eng::MeshComponent(suzanneMaterial, suzanneMesh));
	suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

	auto light = m_Scene->CreateGameObject("Light");
	auto lightComp = new eng::LightComponent();
	lightComp->SetColor(glm::vec3(1.0f));
	light->AddComponenet(lightComp);
	light->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

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
