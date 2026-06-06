#include "editor/EditorManager.h"

#include <iostream>

namespace eng
{
	constexpr int CONSOLE_WINDOW_HEIGHT = 250;
	constexpr int PROPERTIES_WINDOW_WIDTH = 400;
	constexpr int PADDING_OFFSET = 25;

	EditorManager::EditorManager() noexcept
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

	void EditorManager::Draw(int windowWidth, int windowHeight, int fpsCount)
	{
		// TODO: render ImGui windows here
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
		Rect viewport;

		viewport.x = 0;
		viewport.y = 0;

		viewport.width =
			windowWidth - PROPERTIES_WINDOW_WIDTH;

		viewport.height =
			windowHeight - CONSOLE_WINDOW_HEIGHT;

		return viewport;
	}

	void EditorManager::RenderConsoleWindow(int windowWidth, int windowHeight)
	{
		//// create a console window at the bottom of the screen, 
		//// which will be used to display the logs and other information about the application
		//ImGui::Begin(m_ConsoleWindowName.c_str(), nullptr,
		//	ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		//	ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		//	ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

		//// set the position and size of the console window
		//auto windowPos = ImVec2(0, windowHeight - CONSOLE_WINDOW_HEIGHT);
		//auto windowSize = ImVec2(windowWidth - PROPERTIES_WINDOW_WIDTH, CONSOLE_WINDOW_HEIGHT);

		//ImGui::SetWindowPos(m_ConsoleWindowName.c_str(), windowPos);
		//ImGui::SetWindowSize(m_ConsoleWindowName.c_str(), windowSize);

		//auto logEntry = Logger::ReadLogMessage();
		//if (!logEntry.message.empty())
		//{
		//	m_ConsoleMessages.push_front(logEntry.message);
		//}

		//for (const auto& msg : m_ConsoleMessages)
		//{
		//	ImGui::TextWrapped("%s", msg.c_str());
		//}

		//ImGui::End();

		// New Method

		// Window setup
		auto windowPos = ImVec2(0, windowHeight - CONSOLE_WINDOW_HEIGHT);
		auto windowSize = ImVec2(windowWidth - PROPERTIES_WINDOW_WIDTH, CONSOLE_WINDOW_HEIGHT);

		ImGui::SetNextWindowPos(windowPos);
		ImGui::SetNextWindowSize(windowSize);

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(m_ConsoleWindowName.c_str(), nullptr, flags);

		// Read new log entry
		auto logEntry = Logger::ReadLogMessage();
		bool newLogAdded = false;

		if (!logEntry.message.empty())
		{
			m_ConsoleMessages.push_back(logEntry.message);
			newLogAdded = true;

			// Limit memory usage (ring buffer behavior)
			constexpr size_t MAX_LOGS = 2048;
			if (m_ConsoleMessages.size() > MAX_LOGS)
				m_ConsoleMessages.erase(m_ConsoleMessages.begin());
		}

		for (const auto& msg : m_ConsoleMessages)
		{
			ImGui::TextUnformatted(msg.c_str());
		}

		// Auto-scroll
		if (newLogAdded)
		{
			ImGui::SetScrollHereY(1.0f);
		}

		ImGui::End();

	}

	void EditorManager::RenderPropertiesWindow(int windowWidth, int windowHeight)
	{
		auto windowPos = ImVec2(windowWidth - PROPERTIES_WINDOW_WIDTH, 0);
		auto windowSize = ImVec2(PROPERTIES_WINDOW_WIDTH, windowHeight);

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
		ImGui::Begin("Debug");

		ImGui::Text("FPS: %d", fpsCount);

		ImGui::End();
	}
}
