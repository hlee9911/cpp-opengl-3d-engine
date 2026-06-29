#pragma once

#include "input/InputManager.h"
#include "graphics/GraphicsAPI.h"
#include "graphics/Texture.h"
#include "graphics/FrameBuffer.h"
#include "render/RenderQueue.h"
#include "io/FileSystem.h"
#include "physics/PhysicsManager.h"
#include "audio/AudioManager.h"
#include "font/FontManager.h"
#include "editor/EditorManager.h"
#include "scene/components/ui/UIInputSystem.h"
#include "scene/Scene.h"
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
		void SetCursorEnabled(bool enabled);

		void SetApplication(Application* app);
		Application* GetApplication();
		
		InputManager& GetInputManager();
		GraphicsAPI& GetGraphicsAPI();
		RenderQueue& GetRenderQueue();
		FileSystem& GetFileSystem();
		TextureManager& GetTextureManager();
		PhysicsManager& GetPhysicsManager();
		AudioManager& GetAudioManager();
		FontManager& GetFontManager();
		UIInputSystem& GetUIInputSystem();
		EditorManager& GetEditorManager();
		FrameBuffer& GetFrameBuffer();

		// void SetScene(Scene* scene) noexcept { m_CurrentScene.reset(scene); }
		void SetScene(const shared<Scene>& scene) { m_CurrentScene = scene; }
		const shared<Scene>& GetScene() const { return m_CurrentScene; }

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
		AudioManager m_AudioManager;
		FontManager m_FontManager;
		UIInputSystem m_UIInputSystem;
		EditorManager m_EditorManager;
		FrameBuffer m_FrameBuffer;

		shared<Scene> m_CurrentScene;

		float m_FPS = 0.0f;
		float m_FPSTimer = 0.0f;
		int m_FrameCount = 0;

		int m_WindowWidth = 0;
		int m_WindowHeight = 0;
	};
}
