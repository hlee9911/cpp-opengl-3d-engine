#pragma once;
#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <chrono>

struct GLFWwindow;

namespace eng
{
	class Application;

	class Engine
	{
	public:
		bool Init(int width, int height);
		void Run();
		void Destroy();

		void SetApplication(Application* app);
		Application* GetApplication();

	private:
		std::unique_ptr<Application> m_Application;
		std::chrono::steady_clock::time_point m_LastFrameTime;
		GLFWwindow* m_Window = nullptr;

	};
}

#endif // ENGINE_H
