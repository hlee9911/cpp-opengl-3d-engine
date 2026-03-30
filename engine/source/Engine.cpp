#include "Engine.h"
#include "Application.h"
#include "scene/GameObject.h"
#include "scene/Component.h"
#include "scene/components/CameraComponent.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace eng
{
	/// <summary>
	/// This function is called by GLFW when a key event occurs
	/// </summary>
	/// <param name="window"></param>
	/// <param name="key"></param>
	/// <param name="scancode"></param>
	/// <param name="action"></param>
	/// <param name="mods"></param>
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int _)
	{
		Engine& engine = Engine::GetInstance();
		InputManager& inputManager = engine.GetInputManager();

		if (action == GLFW_PRESS)
		{
			inputManager.SetKeyPressed(key, true);
		}
		else if (action == GLFW_RELEASE)
		{
			inputManager.SetKeyPressed(key, false);
		}
	}

	/// <summary>
	/// This function is caleed by GLFW when mouse button event occurs
	/// </summary>
	/// <param name="window"></param>
	/// <param name="button"></param>
	/// <param name="action"></param>
	/// <param name="_"></param>
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int _)
	{
		Engine& engine = Engine::GetInstance();
		InputManager& inputManager = engine.GetInputManager();

		if (action == GLFW_PRESS)
		{
			inputManager.SetMouseButtonPressed(button, true);
		}
		else if (action == GLFW_RELEASE)
		{
			inputManager.SetMouseButtonPressed(button, false);
		}
	}

	/// <summary>
	/// This function is called by GLFW when mouse position changes
	/// </summary>
	/// <param name="window"></param>
	/// <param name="xpos"></param>
	/// <param name="ypos"></param>
	void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Engine& engine = Engine::GetInstance();
		InputManager& inputManager = engine.GetInputManager();

		inputManager.SetMousePositionOld(inputManager.GetMousePositionCurrent());

		glm::vec2 currentPos(static_cast<float>(xpos), static_cast<float>(ypos));
		inputManager.SetMousePositionCurrent(currentPos);

		inputManager.SetMousePositionChanged(true);
	}

	Engine& Engine::GetInstance()
	{
		static Engine instance;
		return instance;
	}

	bool Engine::Init(int width, int height)
	{
		if (!m_Application)
		{
			return false;
		}

		Scene::RegisterTypes();
		m_Application->RegisterTypes();

		if (!glfwInit())
		{
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window
		m_Window = glfwCreateWindow(width, height, "Engine", nullptr, nullptr);

		if (m_Window == nullptr)
		{
			ERROR("Error creating window");
			// std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			return false;
		}

		// set keys, mouse button, and mouse cursor callback
		glfwSetKeyCallback(m_Window, keyCallback);
		glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor and capture it within the window

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			ERROR("Error initializing GLEW");
			// std::cout << "Error initializing GLEW" << std::endl;
			glfwTerminate();
			return false;
		}

		m_GraphicsAPI.Init();
		m_PhysicsManager.Init();
		m_AudioManager.Init();
		return m_Application->Init();
	}

	void Engine::Run()
	{
		if (!m_Application) return;

		m_LastFrameTime = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(m_Window) && !m_Application->NeedsToBeClosed())
		{
			glfwPollEvents(); // process window events

			// Calculate delta time
			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_LastFrameTime).count();
			m_LastFrameTime = now;

			// Update physics
			m_PhysicsManager.Update(deltaTime);

			// Update application
			m_Application->Update(deltaTime);
		
			// Clear screen and buffers
			m_GraphicsAPI.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_GraphicsAPI.ClearBuffers();

			// Collect current camera data
			CameraData cameraData;
			List<LightData> lights;

			int width = 0;
			int height = 0;
			glfwGetWindowSize(m_Window, &width, &height);
			float aspect = static_cast<float>(width) / static_cast<float>(height);

			if (m_CurrentScene)
			{
				if (auto cameraObject = m_CurrentScene->GetMainCamera())
				{
					// logic for matrices
					auto cameraComponent = cameraObject->GetComponent<CameraComponent>();
					if (cameraComponent)
					{
						cameraData.viewMatrix = cameraComponent->GetViewMatrix();
						cameraData.projectionMatrix = cameraComponent->GetProjectionMatrix(aspect);
						cameraData.position = cameraObject->GetWorldPosition();
					}
				}

				lights = m_CurrentScene->CollectLights();
			}

			// Draw render queue
			m_RenderQueue.Draw(m_GraphicsAPI, cameraData, lights);

			// Swap buffers and render
			glfwSwapBuffers(m_Window);

			// before we move onto the nextframe, we set the current mouse position to the old one
			// m_InputManager.SetMousePositionOld(m_InputManager.GetMousePositionCurrent());
			m_InputManager.SetMousePositionChanged(false);
		}
	}

	void Engine::Destroy()
	{
		if (m_Application)
		{
			m_Application->Destroy();
			m_Application.reset();
			glfwTerminate();
			m_Window = nullptr;
		}
	}

	void Engine::SetApplication(Application* app)
	{
		m_Application.reset(app);
	}

	Application* Engine::GetApplication()
	{
		return m_Application.get();
	}

	InputManager& Engine::GetInputManager() noexcept
	{
		return m_InputManager;
	}

	GraphicsAPI& Engine::GetGraphicsAPI() noexcept
	{
		return m_GraphicsAPI;
	}

	RenderQueue& Engine::GetRenderQueue() noexcept
	{
		return m_RenderQueue;
	}

	FileSystem& Engine::GetFileSystem() noexcept
	{
		return m_FileSystem;
	}

	TextureManager& Engine::GetTextureManager() noexcept
	{
		return m_TextureManager;
	}

	PhysicsManager& Engine::GetPhysicsManager() noexcept
	{
		return m_PhysicsManager;
	}

	AudioManager& Engine::GetAudioManager() noexcept
	{
		return m_AudioManager;
	}
}
