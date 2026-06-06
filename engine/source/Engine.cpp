#include "Engine.h"
#include "Application.h"
#include "scene/GameObject.h"
#include "scene/Component.h"
#include "scene/components/CameraComponent.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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
	/// This function is called by GLFW when mouse button event occurs
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
			inputManager.SetMouseButtonWasPressed(button, true);
		}
		else if (action == GLFW_RELEASE)
		{
			inputManager.SetMouseButtonPressed(button, false);
			inputManager.SetMouseButtonWasReleased(button, true);
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

		if (inputManager.GetMousePositionCurrent() == glm::vec2(0.0f))
		{
			// if its the first time we get the mouse position, 
			// we set both old and current to the same value to prevent a large delta on the first frame
			glm::vec2 initialPos(static_cast<float>(xpos), static_cast<float>(ypos));
			inputManager.SetMousePositionOld(initialPos);
			inputManager.SetMousePositionCurrent(initialPos);
			return;
		}

		inputManager.SetMousePositionOld(inputManager.GetMousePositionCurrent());

		glm::vec2 currentPos(static_cast<float>(xpos), static_cast<float>(ypos));
		inputManager.SetMousePositionCurrent(currentPos);

		inputManager.SetMousePositionChanged(true);
	}

	/// <summary>
	/// This function is called by GLFW when the window is resized, 
	/// and it updates the OpenGL viewport to match the new window size
	/// </summary>
	/// <param name="window"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	void windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		//Engine& engine = Engine::GetInstance();
		//engine.GetGraphicsAPI().SetViewport(0, 0, width, height);
		Engine& engine = Engine::GetInstance();

		Rect viewport =
			engine.GetEditorManager().GetViewportRect(
				width,
				height);

		engine.GetGraphicsAPI().SetViewport(
			viewport.x,
			viewport.y,
			viewport.width,
			viewport.height);
	}

	Engine& Engine::GetInstance()
	{
		static Engine instance;
		return instance;
	}

	bool Engine::Init(int width, int height)
	{
		m_WindowWidth = width;
		m_WindowHeight = height;

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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window
		m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "Engine", nullptr, nullptr);

		if (m_Window == nullptr)
		{
			Logger::Error("Error creating window");
			// std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			return false;
		}

		// set keys, mouse button, and mouse cursor callback
		glfwSetKeyCallback(m_Window, keyCallback);
		glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
		glfwSetWindowSizeCallback(m_Window, windowSizeCallback);
		// glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor and capture it within the window

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1); // Enable VSync

		if (glewInit() != GLEW_OK)
		{
			Logger::Error("Error initializing GLEW");
			// std::cout << "Error initializing GLEW" << std::endl;
			glfwTerminate();
			return false;
		}

		// ============ IMGUI TEST ============
		// setup ImGui context and initialize it for GLFW and OpenGL
		/*IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 460");*/
		// ====================================

		m_EditorManager.Init(m_Window);
		m_GraphicsAPI.Init();
		
		// set the initial viewport with ImGui windows taken into account

		/*int windowWidth = 0;
		int windowHeight = 0;

		glfwGetWindowSize(
			m_Window,
			&windowWidth,
			&windowHeight);

		Rect viewport =
			m_EditorManager.GetViewportRect(
				windowWidth,
				windowHeight);

		m_GraphicsAPI.SetViewport(
			viewport.x,
			viewport.y,
			viewport.width,
			viewport.height);*/

		Rect viewport =
			m_EditorManager.GetViewportRect(
				m_WindowWidth,
				m_WindowHeight);

		m_GraphicsAPI.SetViewport(
			viewport.x,
			viewport.y,
			viewport.width,
			viewport.height
		);

		// m_GraphicsAPI.SetViewport(0, 0, m_WindowWidth, m_WindowHeight);
		m_PhysicsManager.Init();
		m_AudioManager.Init();
		m_RenderQueue.Init();
		m_FontManager.Init();

		m_EditorManager.SetFont("assets/fonts/arial.ttf", 16.0f);

		return m_Application->Init();
	}

	void Engine::Run()
	{
		if (!m_Application) return;

		m_LastFrameTime = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(m_Window) && !m_Application->NeedsToBeClosed())
		{
			glfwPollEvents(); // process window events

			// ============ IMGUI TEST ============
			/*ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();*/
			m_EditorManager.ProcessNewFrame();
			// ====================================

			// Calculate delta time
			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_LastFrameTime).count();
			m_LastFrameTime = now;

			// FPS calculation
			m_FPSTimer += deltaTime;
			m_FrameCount++;

			if (m_FPSTimer >= 1.0f)
			{
				m_FPS = static_cast<float>(m_FrameCount) / m_FPSTimer;

				Logger::Log("FPS: " + std::to_string(static_cast<int>(std::round(m_FPS))));

				m_FrameCount = 0;
				m_FPSTimer = 0.0f;
			}

			// Update physics
			m_PhysicsManager.Update(deltaTime);

			// Update UI input system
			if (m_UIInputSystem.IsActive())
			{
				m_UIInputSystem.Update(deltaTime);
			}

			// Update ImGui Editor windows
			m_EditorManager.Update(deltaTime);

			// Update application
			m_Application->Update(deltaTime);
		
			// Clear screen and buffers
			// m_GraphicsAPI.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
						cameraData.orthoMatrix = glm::ortho(
							0.0f, static_cast<float>(width),
							0.0f, static_cast<float>(height)
						);
						cameraData.position = cameraObject->GetWorldPosition();
					}
				}

				lights = m_CurrentScene->CollectLights();
			}

			// Draw render queue
			m_RenderQueue.Draw(m_GraphicsAPI, cameraData, lights);

			// ============ IMGUI TEST ============
			// Build editor/UI windows
			/*ImGui::Begin("Engine Stats");
			ImGui::Text("FPS: %.1f", m_FPS);
			ImGui::End();*/
			//ImGui::ShowDemoWindow();

			// Render ImGui
			//ImGui::Render();
			//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			m_EditorManager.Draw(width, height, static_cast<int>(std::round(m_FPS)));
			// ====================================

			// Swap buffers and render
			glfwSwapBuffers(m_Window);

			// before we move onto the nextframe, we set the current mouse position to the old one
			// m_InputManager.SetMousePositionOld(m_InputManager.GetMousePositionCurrent());
			// m_InputManager.SetMousePositionChanged(false);
			m_InputManager.ClearStates();
		}

		m_Application.reset(nullptr); // ensures a clean shutdown of the application
	}

	void Engine::Destroy()
	{
		if (m_Application)
		{
			m_Application->Destroy();
			m_Application.reset();

			// ============ IMGUI TEST ============
			/*ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();*/
			m_EditorManager.Destroy();
			// ====================================

			glfwTerminate();

			m_Window = nullptr;
		}
	}

	void Engine::SetCursorEnabled(bool enabled)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
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

	FontManager& Engine::GetFontManager() noexcept
	{
		return m_FontManager;
	}

	UIInputSystem& Engine::GetUIInputSystem() noexcept
	{
		return m_UIInputSystem;
	}

	EditorManager& Engine::GetEditorManager() noexcept
	{
		return m_EditorManager;
	}
}
