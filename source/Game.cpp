#include "Game.h"
#include "TestObject.h"
#include "Core.h"
#include "Player.h"
#include "Bullet.h"
#include "JumpPlatform.h"

void Game::RegisterTypes()
{
	// engine call this during Engine::Init() after engine-side types are registered
	Player::Register();
	Bullet::Register();
	JumpPlatform::Register();
}

bool Game::Init()
{

// using scene.sc to load scene properties 
#if 0
	auto& fs = eng::Engine::GetInstance().GetFileSystem();
	auto texture = eng::Texture::Load("brick.png");

	m_Scene = new eng::Scene();
	eng::Engine::GetInstance().SetScene(m_Scene);

	auto player = m_Scene->CreateGameObject<Player>("Player");
	player->Init();
	m_Scene->SetMainCamera(player);

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
	
	auto mesh = eng::Mesh::CreateBox();

	//auto objectA = m_Scene->CreateGameObject("ObjectA");
	//objectA->AddComponenet(new eng::MeshComponent(material, mesh));
	//objectA->SetPosition(glm::vec3(1.0f, 0.0f, -5.0f));

	auto objectB = m_Scene->CreateGameObject("ObjectB");
	objectB->AddComponenet(new eng::MeshComponent(material, mesh));
	objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

	auto objectC = m_Scene->CreateGameObject("ObjectC");
	objectC->AddComponenet(new eng::MeshComponent(material, mesh));
	objectC->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
	objectC->SetRotation(glm::vec3(1.0f, 0.0f, 1.0f));
	objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

	//auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
	//auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

	// auto suzanneObj = m_Scene->CreateGameObject("Suzanne");
	// suzanneObj->AddComponenet(new eng::MeshComponent(suzanneMaterial, suzanneMesh));

	auto suzanneObj = eng::GameObject::LoadGLTF("models/suzanne/Suzanne.gltf");
	suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

	auto light = m_Scene->CreateGameObject("Light");
	auto lightComp = new eng::LightComponent();
	lightComp->SetColor(glm::vec3(1.0f));
	light->AddComponenet(lightComp);
	light->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	
	// Create a ground plane
	auto ground = m_Scene->CreateGameObject("Ground");
	ground->SetPosition(glm::vec3(0.0f, -5.0f, 0.0f));

	glm::vec3 groundExtents(20.0f, 2.0f, 20.0f);
	auto groundMesh = eng::Mesh::CreateBox(groundExtents);
	ground->AddComponenet(new eng::MeshComponent(material, groundMesh));

	auto groundCollider = std::make_shared<eng::BoxCollider>(groundExtents);
	auto groundBody = std::make_shared<eng::RigidBody>(
		eng::BodyType::Static, 
		groundCollider,
		0.0f, // mass
		0.5f  // friction
	);
	ground->AddComponenet(new eng::PhysicsComponent(groundBody));

	// Create a dynamic cube
	auto boxObj = m_Scene->CreateGameObject("FallingBox");
	boxObj->AddComponenet(new eng::MeshComponent(material, mesh));
	boxObj->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	boxObj->SetRotation(glm::quat(glm::vec3(1.0f, 2.0f, 0.0f)));
	auto boxCollider = std::make_shared<eng::BoxCollider>(glm::vec3(1.0f));
	auto boxBody = std::make_shared<eng::RigidBody>(
		eng::BodyType::Dynamic,
		boxCollider,
		5.0f, // mass
		0.5f  // friction
	);
	boxObj->AddComponenet(new eng::PhysicsComponent(boxBody));
	
	// camera->SetPosition(glm::vec3(0.0f, 1.0f, 7.0f));
#endif
	
	// commenting out to test 2d rendering
	//auto scene = eng::Scene::Load("scenes/scene.sc");
	//m_Scene = scene;
	//eng::Engine::GetInstance().SetScene(scene);

	m_Scene = std::make_shared<eng::Scene>();
	eng::Engine::GetInstance().SetScene(m_Scene);

	auto sprite = m_Scene->CreateGameObject("Sprite");
	auto spriteComponent = new eng::SpriteComponent();

	auto texture = eng::Texture::Load("textures/brick.png");
	spriteComponent->SetTexture(texture);

	sprite->AddComponenet(spriteComponent);
	sprite->SetPosition2D(glm::vec2(500.0f, 500.0f));

	spriteComponent->SetSize(glm::vec2(200.0f, 100.0f));
	spriteComponent->SetUpperRightUV(glm::vec2(2.0f, 1.0f));
	sprite->SetRotation2D(glm::radians(45.0f));

	auto camera = m_Scene->CreateGameObject("Camera");
	auto cameraComponent = new eng::CameraComponent();
	camera->AddComponenet(cameraComponent);
	m_Scene->SetMainCamera(camera);

	// UI Test
	auto canvas = m_Scene->CreateGameObject("Canvas");
	auto canvasComponent = new eng::CanvasComponent();
	canvas->AddComponenet(canvasComponent);

	auto text = m_Scene->CreateGameObject("Text", canvas);
	text->SetPosition2D(glm::vec2(300.0f, 300.0f));
	auto textComponent = new eng::TextComponent();
	text->AddComponenet(textComponent);
	textComponent->SetText("Some Text");
	textComponent->SetFont("fonts/arial.ttf", 24);
	textComponent->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

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
