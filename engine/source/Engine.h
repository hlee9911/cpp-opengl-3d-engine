#pragma once;
#ifndef ENGINE_H
#define ENGINE_H

#include "input/InputManager.h"
#include <memory>
#include <chrono>

struct GLFWwindow;

namespace eng
{
	class Application;

	class Engine
	{
	public:
		// Singleton access
		static Engine& GetInstance();

	private:
		Engine() noexcept = default;
		Engine(const Engine&) noexcept = delete;
		Engine(Engine&&) noexcept = delete;
		Engine& operator=(const Engine&) noexcept = delete;
		Engine& operator=(Engine&&) noexcept = delete;

	public:
		bool Init(int width, int height);
		void Run();
		void Destroy();

		void SetApplication(Application* app);
		Application* GetApplication();
		
		InputManager& GetInputManager() noexcept;

	private:
		std::unique_ptr<Application> m_Application;
		std::chrono::steady_clock::time_point m_LastFrameTime;
		GLFWwindow* m_Window = nullptr;
		InputManager m_InputManager;
	};
}

#endif // ENGINE_H
