#include "Engine.h"
#include "Application.h"

namespace eng
{
	bool Engine::Init()
	{
		if (m_Application)
		{
			return false;
		}

		return m_Application->Init();
	}

	void Engine::Run()
	{
		if (!m_Application) return;

		m_LastFrameTime = std::chrono::high_resolution_clock::now();
		while(!m_Application->NeedsToBeClosed())
		{
			auto now = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(now - m_LastFrameTime).count();
			m_LastFrameTime = now;

			m_Application->Update(deltaTime);
		}
	}

	void Engine::Destroy()
	{
		if (m_Application)
		{
			m_Application->Destroy();
			m_Application.reset();
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
