#pragma once;

#include "input/InputManager.h"
#include "graphics/GraphicsAPI.h"
#include "graphics/Texture.h"
#include "render/RenderQueue.h"
#include "scene/Scene.h"
#include "io/FileSystem.h"
#include "physics/PhysicsManager.h"
#include "Core.h"

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
		GraphicsAPI& GetGraphicsAPI() noexcept;
		RenderQueue& GetRenderQueue() noexcept;
		FileSystem& GetFileSystem() noexcept;
		TextureManager& GetTextureManager() noexcept;
		PhysicsManager& GetPhysicsManager() noexcept;

		void SetScene(Scene* scene) noexcept { m_CurrentScene.reset(scene); }
		Scene* GetScene() const noexcept { return m_CurrentScene.get(); }

	private:
		unique<Application> m_Application;
		std::chrono::steady_clock::time_point m_LastFrameTime;
		GLFWwindow* m_Window = nullptr;
		InputManager m_InputManager;
		GraphicsAPI m_GraphicsAPI;
		RenderQueue m_RenderQueue;
		FileSystem m_FileSystem;
		TextureManager m_TextureManager;
		PhysicsManager m_PhysicsManager;
		unique<Scene> m_CurrentScene;
	};
}
