#include "editor/EditorManager.h"
#include "Engine.h"

#include <iostream>

namespace eng
{
	constexpr int CONSOLE_WINDOW_HEIGHT = 250;
	constexpr int PROPERTIES_WINDOW_WIDTH = 400;
	constexpr int PADDING_OFFSET = 25;

	EditorManager::EditorManager() noexcept : 
		m_ConsoleMessages{}
	{

	}

	EditorManager::~EditorManager() noexcept
	{

	}

	bool EditorManager::Init(GLFWwindow* window)
	{
		// setup ImGui context and initialize it for GLFW and OpenGL
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		//ImGuiIO& io = ImGui::GetIO();
		//(void)io;

		// ImGui::StyleColorsDark();

		if (!ImGui_ImplOpenGL3_Init("#version 460"))
		{
			Logger::Error("Failed to initialize ImGui OpenGL3 backend");
			return false;
		}

		if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
		{
			Logger::Error("Failed to initialize ImGui GLFW backend");
			return false;
		}

		return true;
	}

	void EditorManager::SetFont(const std::string& fontPath, float fontSize)
	{
		// setting up ImGui font
		ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
		ImGui::GetIO().Fonts->Build();
	}

	void EditorManager::ProcessNewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void EditorManager::Update(float deltaTime)
	{

	}

	void EditorManager::Draw(
		int windowWidth, int 
		windowHeight, 
		int fpsCount,
		unsigned int framebufferTexture)
	{
		RenderViewportWindow(
			windowWidth,
			windowHeight,
			framebufferTexture);
		RenderConsoleWindow(windowWidth, windowHeight);
		RenderPropertiesWindow(windowWidth, windowHeight);
		RenderDebugWindow(windowWidth, windowHeight, fpsCount);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void EditorManager::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	Rect EditorManager::GetViewportRect(int windowWidth, int windowHeight) const
	{
		/*Rect viewport;

		viewport.x = 0;
		viewport.y = 0;

		viewport.width =
			windowWidth - PROPERTIES_WINDOW_WIDTH;

		viewport.height =
			windowHeight - CONSOLE_WINDOW_HEIGHT;

		return viewport;*/

		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f)
		{
			return {
				0, 0,
				static_cast<int>(m_ViewportSize.x),
				static_cast<int>(m_ViewportSize.y)
			};
		}
		return {
			0, 0,
			windowWidth - PROPERTIES_WINDOW_WIDTH,
			windowHeight - CONSOLE_WINDOW_HEIGHT
		};
	}

	void EditorManager::RenderViewportWindow(
		int windowWidth, 
		int windowHeight, 
		unsigned int framebufferTexture)
	{
		// Dock the viewport panel to the top-left, leaving room for side/bottom editor panels
		ImVec2 windowPos(0, 0);

		ImVec2 windowSize(
			static_cast<float>(
				windowWidth - PROPERTIES_WINDOW_WIDTH),
			static_cast<float>(
				windowHeight - CONSOLE_WINDOW_HEIGHT));

		ImGui::SetNextWindowPos(windowPos);
		ImGui::SetNextWindowSize(windowSize);

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse;

		/*ImGui::Begin(m_ViewportWindowName.c_str(), nullptr, flags);

		m_ViewportPosition = ImGui::GetCursorScreenPos();
		m_ViewportSize = ImGui::GetContentRegionAvail();

		ImGui::Image(
			(ImTextureID)(intptr_t)framebufferTexture,
			m_ViewportSize,
			ImVec2(0, 1),
			ImVec2(1, 0));

		ImGui::End();*/

		ImGui::Begin(m_ViewportWindowName.c_str(), nullptr, flags);

		// Use all remaining space inside the window for the rendered scene
		ImVec2 imageSize = ImGui::GetContentRegionAvail();

		// Draw the FBO color texture into the viewport panel
		ImGui::Image(
			(ImTextureID)(intptr_t)framebufferTexture,
			imageSize,
			ImVec2(0, 1),
			ImVec2(1, 0));

		// Capture ACTUAL drawn image rect
		// Store the exact screen-space rect of the image for mouse conversion
		m_ViewportImageMin = ImGui::GetItemRectMin();
		m_ViewportSize = ImGui::GetItemRectSize();
		m_ViewportHovered = ImGui::IsItemHovered();

		ImGui::End();
	}

	void EditorManager::RenderConsoleWindow(int windowWidth, int windowHeight)
	{
		// Position the console panel at the bottom-left of the editor
		auto windowPos = ImVec2(0.0f, static_cast<float>(windowHeight - CONSOLE_WINDOW_HEIGHT));
		auto windowSize = ImVec2(static_cast<float>(windowWidth - PROPERTIES_WINDOW_WIDTH), 
								 static_cast<float>(CONSOLE_WINDOW_HEIGHT));

		ImGui::SetNextWindowPos(windowPos);
		ImGui::SetNextWindowSize(windowSize);

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(m_ConsoleWindowName.c_str(), nullptr, flags);

		// Pull one new log entry from Logger each frame (if any)
		auto logEntry = Logger::ReadLogMessage();
		bool newLogAdded = false;

		if (!logEntry.message.empty())
		{
			// Store the full entry so we keep both message + type/flag
			m_ConsoleMessages.push_back(logEntry);
			newLogAdded = true;

			// Prevent unbounded memory growth
			constexpr size_t MAX_LOGS = 2048;
			if (m_ConsoleMessages.size() > MAX_LOGS)
				m_ConsoleMessages.erase(m_ConsoleMessages.begin());
		}

		// Draw every stored log with color based on its type
		for (const auto& entry : m_ConsoleMessages)
		{
			// Temporarily override text color for this line only
			ImGui::PushStyleColor(ImGuiCol_Text, GetLogColor(entry.type));
			// Draw the log message
			ImGui::TextUnformatted(entry.message.c_str());
			// Restore previous text color so other ImGui widgets arent affected
			ImGui::PopStyleColor();
		}

		// Scroll to bottom when a new message arrives
		if (newLogAdded) ImGui::SetScrollHereY(1.0f);
		ImGui::End();
	}

	void EditorManager::RenderPropertiesWindow(int windowWidth, int windowHeight)
	{
		auto windowPos = ImVec2(static_cast<float>(windowWidth - PROPERTIES_WINDOW_WIDTH), 0.0f);
		auto windowSize = ImVec2(static_cast<float>(PROPERTIES_WINDOW_WIDTH), 
								 static_cast<float>(windowHeight - CONSOLE_WINDOW_HEIGHT));

		ImGui::SetNextWindowPos(windowPos);
		ImGui::SetNextWindowSize(windowSize);

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(m_PropertiesWindowName.c_str(), nullptr, flags);

		// slider widget
		//if (!Objects.empty())
		//{
		//	auto position = Objects[0]->GetTransform().GetPosition();
		//	ImGui::SliderFloat3("Position", &position.x, -10.0f, 10.0f, "%.2f");
		//	Objects[0]->GetTransform().SetPosition(position.x, position.y, position.z);

		//	auto rotation = Objects[0]->GetTransform().GetRotation();
		//	ImGui::SliderFloat3("Rotation", &rotation.x, -180.0f, 180.0f, "%.2f");
		//	Objects[0]->GetTransform().SetRotation(rotation.x, rotation.y, rotation.z);

		//	auto scale = Objects[0]->GetTransform().GetScale();
		//	ImGui::SliderFloat3("Scale", &scale.x, 0.001f, 10.0f, "%.2f");
		//	Objects[0]->GetTransform().SetScale(scale.x, scale.y, scale.z);
		//}

		ImGui::Separator();

		//ImGui::Button("Crate 1 texture");
		//ImGui::Button("Crate 2 texture");

		ImGui::Separator();

		/*if (!Objects.empty())
		{
			auto isTextured = Objects[0]->IsTextured();
			ImGui::Checkbox("Textured", &isTextured);
			Objects[0]->SetTextured(isTextured);
		}*/

		//ImGui::Checkbox("Light the scene", &isLit);

		ImGui::Separator();

		/*if (!Objects.empty())
		{
			auto color = Objects[0]->GetColor();
			ImGui::ColorEdit4("Color", &color.r);
			Objects[0]->SetColor(color);
		}*/

		ImGui::Separator();
		ImGui::End();
	}

	void EditorManager::RenderDebugWindow(int windowWidth, int windowHeight, int fpsCount)
	{
		// Bottom-right corner: sits under Properties, beside Console
		ImGui::SetNextWindowPos(ImVec2(
			static_cast<float>(windowWidth - PROPERTIES_WINDOW_WIDTH),
			static_cast<float>(windowHeight - CONSOLE_WINDOW_HEIGHT)));

		ImGui::SetNextWindowSize(ImVec2(
			static_cast<float>(PROPERTIES_WINDOW_WIDTH),
			static_cast<float>(CONSOLE_WINDOW_HEIGHT)));

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(m_DebugWindowName.c_str(), nullptr, flags);

		// --- Performance ---
		ImGui::Text("FPS: %d", fpsCount);

		// Smooth FPS over last N frames (store m_FpsHistory in EditorManager)
		// ImGui::PlotLines("FPS", m_FpsHistory.data(), (int)m_FpsHistory.size(), ...);

		ImGui::Separator();
		// --- Memory (placeholder until you wire platform APIs) ---

		// ImGui::Text("Memory: %.2f MB", GetProcessMemoryMB());

		ImGui::Separator();

		// --- Profiler (expand later with scoped timers) ---

		/*ImGui::Text("Frame: %.2f ms", m_LastFrameTimeMs);
		ImGui::Text("Update: %.2f ms", m_UpdateTimeMs);
		ImGui::Text("Render: %.2f ms", m_RenderTimeMs);*/

		ImGui::End();
	}

	ImVec4 EditorManager::GetLogColor(LogType type) const
	{
		switch (type)
		{
		case LogType::LOG_INFO:
			return ImVec4(0.2f, 1.0f, 0.2f, 1.0f);   // green
		case LogType::LOG_WARNING:
			return ImVec4(1.0f, 1.0f, 0.2f, 1.0f);   // yellow
		case LogType::LOG_ERROR:
			return ImVec4(1.0f, 0.3f, 0.3f, 1.0f);   // red
		default:
			return ImGui::GetStyleColorVec4(ImGuiCol_Text); // fallback to default text color
		}
	}

	std::optional<glm::vec2> EditorManager::ScreenToGameUI(const glm::vec2& screenMouse) const
	{
		// Bail out if we don't know the viewport image or UI render size yet
		if (m_ViewportSize.x <= 0.0f || m_ViewportSize.y <= 0.0f ||
			m_UIRenderWidth <= 0 || m_UIRenderHeight <= 0)
			return std::nullopt;

		// Mouse relative to the top-left of the ImGui viewport image
		const float localX = screenMouse.x - m_ViewportImageMin.x;
		const float localY = screenMouse.y - m_ViewportImageMin.y;

		// Ignore clicks outside the game viewport (Properties, Console, etc.)
		if (localX < 0.0f || localY < 0.0f ||
			localX > m_ViewportSize.x || localY > m_ViewportSize.y)
			return std::nullopt;

		// UI uses a different resolution than the on-screen image, so scale into UI space
		const float uiW = static_cast<float>(m_UIRenderWidth);
		const float uiH = static_cast<float>(m_UIRenderHeight);
		const float uiX = localX * (uiW / m_ViewportSize.x);

		// Convert from top-left screen space to bottom-left UI space
		const float uiY = uiH - (localY * (uiH / m_ViewportSize.y));
		return glm::vec2(uiX, uiY);
	}

	bool EditorManager::IsMouseOverViewport() const
	{
		return false;
	}

	void EditorManager::SetUIRenderSize(int width, int height)
	{
		m_UIRenderWidth = width;
		m_UIRenderHeight = height;
	}
}
