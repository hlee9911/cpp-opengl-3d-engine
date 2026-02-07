#include "Game.h"
#include "TestObject.h"
#include "Core.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool Game::Init()
{
	auto& fs = eng::Engine::GetInstance().GetFileSystem();
	auto path = fs.GetAssetFolder() / "brick.png";

	int width, height, channels;
	unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

	if (data)
	{
		LOG("Image loaded");
	}

	m_Scene = new eng::Scene();

	auto camera = m_Scene->CreateGameObject("Camera");
	camera->AddComponenet(new eng::CameraComponent());
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera->AddComponenet(new eng::PlayerControllerComponent());

	m_Scene->SetMainCamera(camera);

	m_Scene->CreateGameObject<TestObject>("TestObject");

	std::string vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;

		out vec3 vColor;

		uniform mat4 uModel;
		uniform mat4 uView;
		uniform mat4 uProjection;

        void main()
        {
			vColor = color;
            gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
        }
    )"; // mvp chain (uProjection * uView * uModel)

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

	auto material = std::make_shared<eng::Material>();
	material->SetShaderProgram(shaderProgram); // set the shader program to the material, and its ready for rendering

	std::vector<float> verticies =
	{
		// positions        // colors
		 0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
		 -0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
	};

	std::vector<unsigned int> indicies =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// top face
		4, 5, 1,
		4, 1, 0,

		// right face
		4, 0, 3,
		4, 3, 7,

		// left face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		3, 2, 6,
		3, 6, 7,

		// back face
		4, 7, 6,
		4, 6, 5
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
	auto mesh = std::make_shared<eng::Mesh>(
		vertexLayout,
		verticies,
		indicies
	);

	auto objectA = m_Scene->CreateGameObject("ObjectA");
	objectA->AddComponenet(new eng::MeshComponent(material, mesh));
	objectA->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

	auto objectB = m_Scene->CreateGameObject("ObjectB");
	objectB->AddComponenet(new eng::MeshComponent(material, mesh));
	objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
	objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

	auto objectC = m_Scene->CreateGameObject("ObjectC");
	objectC->AddComponenet(new eng::MeshComponent(material, mesh));
	objectC->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
	objectC->SetRotation(glm::vec3(1.0f, 0.0f, 1.0f));
	objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

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
