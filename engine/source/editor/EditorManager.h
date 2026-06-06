#pragma once

#include "Core.h"
#include "scene/GameObject.h"
#include "graphics/GraphicsAPI.h"

#include <string>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace eng
{
	class EditorManager
	{
	public:

		EditorManager() noexcept;
		~EditorManager() noexcept;

		bool Init(GLFWwindow* window);
		void SetFont(const std::string& fontPath, float fontSize);
		void ProcessNewFrame();
		void Update(float deltaTime);
		void Draw(int windowWidth, int windowHeight, int fpsCount);
		void Destroy();

		Rect GetViewportRect(int windowWidth,
							 int windowHeight) const;

		ImGuiIO& GetImGuiIO() const noexcept { return ImGui::GetIO(); }

	private:

		void RenderConsoleWindow(int windowWidth, int windowHeight);
		void RenderPropertiesWindow(int windowWidth, int windowHeight);
		void RenderDebugWindow(int windowWidth, int windowHeight, int fpsCount);

	private:

		const std::string m_ConsoleWindowName = "Console";
		const std::string m_PropertiesWindowName = "Properties";
		const std::string m_DebugWindowName = "Debug";

		Deque<std::string> m_ConsoleMessages;

		GameObject* m_SelectedGameObject = nullptr;
	};
}
