#include "Engine.h"
#include "Application.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace eng
{
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

		m_Window = glfwCreateWindow(width, height, "GameDevEngine", nullptr, nullptr);

		if (m_Window == nullptr)
		{
			std::cout << "Error creating window" << std::endl;
			glfwTerminate();
			return false;
		}

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
}
