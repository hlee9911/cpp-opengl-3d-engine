#pragma once

#include "Core.h"
#include "scene/GameObject.h"
#include "graphics/GraphicsAPI.h"

#include <string>
#include <optional>

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
		void Draw(int windowWidth, int windowHeight, int fpsCount, unsigned int framebufferTexture);
		void Destroy();

		Rect GetViewportRect(int windowWidth,
							 int windowHeight) const;

		ImGuiIO& GetImGuiIO() const noexcept { return ImGui::GetIO(); }

		std::optional<glm::vec2> ScreenToGameUI(const glm::vec2& screenMouse) const;
		bool IsMouseOverViewport() const;
		void SetUIRenderSize(int width, int height);

	private:

		void RenderViewportWindow(int windowWidth, int windowHeight, unsigned int framebufferTexture);
		void RenderConsoleWindow(int windowWidth, int windowHeight);
		void RenderPropertiesWindow(int windowWidth, int windowHeight);
		void RenderDebugWindow(int windowWidth, int windowHeight, int fpsCount);

		ImVec4 GetLogColor(LogType type) const;

	private:

		ImVec2 m_ViewportImageMin = ImVec2(0, 0);  // top-left of ImGui::Image (screen space)
		ImVec2 m_ViewportSize = ImVec2(0, 0);     // size of ImGui::Image
		int m_UIRenderWidth = 0;                  // must match CanvasComponent::Flush ortho width
		int m_UIRenderHeight = 0;                 // must match CanvasComponent::Flush ortho height
		bool m_ViewportHovered = false;

		const std::string m_ViewportWindowName = "Viewport";
		const std::string m_ConsoleWindowName = "Console";
		const std::string m_PropertiesWindowName = "Properties";
		const std::string m_DebugWindowName = "Debug";

		Deque<LogEntry> m_ConsoleMessages;

		GameObject* m_SelectedGameObject = nullptr;
	};
}
