#include "Engine.h"
#include "Application.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace eng
{
	/// <summary>
	/// This function is called by GLFW when a key event occurs.
	/// </summary>
	/// <param name="window"></param>
	/// <param name="key"></param>
	/// <param name="scancode"></param>
	/// <param name="action"></param>
	/// <param name="mods"></param>
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

		if (!glfwInit())
		{
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window
		m_Window = glfwCreateWindow(width, height, "GameDevEngine", nullptr, nullptr);

		if (m_Window == nullptr)
		{
			std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			return false;
		}

		// set key callback
		glfwSetKeyCallback(m_Window, keyCallback);

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error initializing GLEW" << std::endl;
			glfwTerminate();
			return false;
		}

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

			// Update application
			m_Application->Update(deltaTime);
		
			// Clear screen and buffers
			m_GraphicsAPI.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			m_GraphicsAPI.ClearBuffers();

			// Draw render queue
			m_RenderQueue.Draw(m_GraphicsAPI);

			// Swap buffers and render
			glfwSwapBuffers(m_Window);
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
}
