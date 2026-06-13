#include "editor/EditorManager.h"
#include "profiler/Profiler.h"
#include "scene/components/MeshComponent.h"
#include "scene/components/CameraComponent.h"
#include "scene/components/PlayerControllerComponent.h"
#include "scene/components/LightComponent.h"
#include "scene/components/AnimationComponent.h"
#include "scene/components/PhysicsComponent.h"
#include "scene/components/AudioComponent.h"
#include "scene/components/AudioListenerComponent.h"
#include "scene/components/ui/UIInputSystem.h"
#include "scene/components/ui/CanvasComponent.h"
#include "render/Material.h"
#include "Engine.h"

namespace eng
{
	constexpr int CONSOLE_WINDOW_HEIGHT = 300;
	constexpr int PROPERTIES_WINDOW_WIDTH = 400;
	constexpr int PADDING_OFFSET = 25;

	EditorManager::EditorManager() noexcept : 
		m_ConsoleMessages{},
		m_DisplayMemory{}
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
		// Refresh memory display values once per second
		m_MemoryRefreshTimer += deltaTime;
		if (m_MemoryRefreshTimer >= 1.0f)
		{
			m_DisplayMemory = MemoryManager::GetProcessMemoryStats();
			m_MemoryRefreshTimer = 0.0f;
		}

		HandleEditorInput();
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

		ImGui::SetNextWindowPos(ImVec2(
			static_cast<float>(windowWidth - PROPERTIES_WINDOW_WIDTH), 0.0f));
		ImGui::SetNextWindowSize(ImVec2(
			static_cast<float>(PROPERTIES_WINDOW_WIDTH),
			static_cast<float>(windowHeight - CONSOLE_WINDOW_HEIGHT)));

		ImGuiWindowFlags flags =
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(m_PropertiesWindowName.c_str(), nullptr, flags);

		ImGui::TextDisabled("Tab: Next Game Object  |  Shift+Tab: Previous Game Object");
		ImGui::TextDisabled("R: Set the player's position to the initial position");
		ImGui::TextDisabled("V: Toggle Editor Mode (Cursor & Input)");
		if (m_EditorCursorEnabled)
		{
			ImGui::Text("Mode: Editor");
		}
		else
		{
			ImGui::Text("Mode: Gameplay");
		}

		ImGui::Separator();

		if (!m_SelectedGameObject)
		{
			ImGui::TextWrapped("No object selected. Press Tab to cycle scene objects.");
			ImGui::End();
			return;
		}

		DrawGameObjectInspector(m_SelectedGameObject);

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

		auto& profiler = Profiler::GetInstance();

		// --------------- FPS --------------------------

		// These only change once per second now
		ImGui::Text("FPS: %.0f", profiler.GetDisplayFps());
		ImGui::Text("Frame: %.2f ms", profiler.GetDisplayFrameMs());

		// Graph can still update every frame (smooth line)

		ImGui::PlotLines(
			"FPS Graph",
			profiler.GetFpsHistory().data(),
			static_cast<int>(profiler.GetFpsHistory().size()),
			0,
			nullptr,
			0.0f,
			120.0f,
			ImVec2(-1, 60));

		ImGui::Separator();

		// --------------- Memory --------------------------

		// Memory also refreshes once per second
		ImGui::Text("Working Set: %.2f MB", m_DisplayMemory.workingSetMB);
		ImGui::Text("Private Usage: %.2f MB", m_DisplayMemory.privateUsageMB);
		ImGui::Text("Peak Working Set: %.2f MB", m_DisplayMemory.peakWorkingSetMB);
		
		ImGui::Separator();

		// --------------- Profiler --------------------------
		
		ImGui::Text("Profiler (1s avg)");

		auto drawSample = [](const char* label, const char* sampleName)
			{
				if (const ProfileSample* sample = Profiler::GetInstance().GetSample(sampleName))
				{
					// Show the 1-second average
					ImGui::Text("%s: %.2f ms", label, sample->displayMs);
				}
			};

		drawSample("Physics", "Physics");
		drawSample("Editor", "Editor");
		drawSample("Game Update", "Game Update");
		drawSample("Render", "Render");
		drawSample("ImGui", "ImGui");

		ImGui::PlotLines(
			"Frame Time (ms)",
			profiler.GetFrameHistory().data(),
			static_cast<int>(profiler.GetFrameHistory().size()),
			0,
			nullptr,
			0.0f,
			33.3f,
			ImVec2(-1, 60));

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
		// Bail out if we dont know the viewport image or UI render size yet
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

	void EditorManager::HandleEditorInput()
	{
		auto& engine = Engine::GetInstance();
		auto& input = engine.GetInputManager();

		// Dont steal Tab while typing in an ImGui text field
		if (ImGui::GetIO().WantCaptureKeyboard) return;

		// Tab = next object, Shift+Tab = previous
		if (input.WasKeyPressed(GLFW_KEY_TAB))
		{
			const bool backward =
				input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT) ||
				input.IsKeyPressed(GLFW_KEY_RIGHT_SHIFT);
			CycleSelection(backward);
		}

		// V = toggle cursor so you can use ImGui during gameplay
		if (input.WasKeyPressed(GLFW_KEY_V))
		{
			bool isUIInputSystemActive = engine.GetUIInputSystem().IsActive();
			m_EditorCursorEnabled = !m_EditorCursorEnabled;
			engine.SetCursorEnabled(m_EditorCursorEnabled && isUIInputSystemActive);
		}
	}

	void EditorManager::CycleSelection(bool backward)
	{
		auto scene = Engine::GetInstance().GetScene();

		if (!scene) return;

		List<GameObject*> objects;
		scene->CollectAllGameObjects(objects);

		// Remove inactive objects so Tab skips hidden stuff (like 3DRoot when menu is up)
		objects.erase(
			std::remove_if(objects.begin(), objects.end(),
				[](GameObject* obj) { return !obj->IsActive(); }),
			objects.end());

		if (objects.empty())
		{
			m_SelectedGameObject = nullptr;
			m_SelectedIndex = -1;
			return;
		}

		// Find current index (selection may have become invalid)
		if (m_SelectedGameObject)
		{
			auto it = std::find(objects.begin(), objects.end(), m_SelectedGameObject);
			m_SelectedIndex = (it != objects.end())
				? static_cast<int>(std::distance(objects.begin(), it))
				: -1;
		}

		// Move forward/backward with wrap-around
		if (backward)
		{
			m_SelectedIndex = (m_SelectedIndex <= 0)
				? static_cast<int>(objects.size()) - 1
				: m_SelectedIndex - 1;
		}
		else
		{
			m_SelectedIndex = (m_SelectedIndex + 1) % static_cast<int>(objects.size());
		}

		m_SelectedGameObject = objects[m_SelectedIndex];
		Logger::Log("Selected: " + m_SelectedGameObject->GetName());
	}

	void EditorManager::DrawGameObjectInspector(GameObject* obj)
	{
		// --- Object header ---
		char buffer[256];
		strncpy_s(buffer, obj->GetName().c_str(), sizeof(buffer));

		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		{
			obj->SetName(buffer);
		}

		bool active = obj->IsActive();
		if (ImGui::Checkbox("Is Active", &active))
		{
			obj->SetActive(active);
		}

		ImGui::Separator();

		// --- Transform (always shown) ---
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			DrawTransformInspector(obj);
		}

		// --- Components ---
		DrawComponentInspectors(obj);
	}

	void EditorManager::DrawTransformInspector(GameObject* obj)
	{
		// Position
		glm::vec3 pos = obj->GetPosition();
		if (ImGui::DragFloat3("Position", &pos.x, 0.1f))
		{
			obj->SetPosition(pos);
			if (auto* physicsComp = obj->GetComponent<PhysicsComponent>())
			{
				physicsComp->GetRigidBody()->SetPosition(pos);
			}
		}

		// Rotation as Euler degrees (easier to edit than quaternions in ImGui)
		glm::vec3 euler = glm::degrees(glm::eulerAngles(obj->GetRotation()));
		if (ImGui::DragFloat3("Rotation", &euler.x, 1.0f))
		{
			obj->SetRotation(glm::quat(glm::radians(euler)));
			if (auto* physicsComp = obj->GetComponent<PhysicsComponent>())
			{
				physicsComp->GetRigidBody()->SetRotation(glm::quat(glm::radians(euler)));
			}
		}

		// Scale
		glm::vec3 scale = obj->GetScale();
		if (ImGui::DragFloat3("Scale", &scale.x, 0.05f, 0.001f, 100.0f))
		{
			obj->SetScale(scale);
			if (auto* physicsComp = obj->GetComponent<PhysicsComponent>())
			{
				physicsComp->GetRigidBody()->SetScale(scale);
			}
		}
	}

	void EditorManager::DrawComponentInspectors(GameObject* obj)
	{
		// Light
		if (auto* lightComp = obj->GetComponent<LightComponent>())
		{
			if (ImGui::CollapsingHeader("Light Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				glm::vec3 lightColor = lightComp->GetColor();
				if (ImGui::ColorEdit3("Light Color", &lightColor.x))
				{
					lightComp->SetColor(lightColor);
				}
			}
		}

		// Camera
		if (auto* cameraComp = obj->GetComponent<CameraComponent>())
		{
			if (ImGui::CollapsingHeader("Camera Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				float fov = cameraComp->GetFov();
				if (ImGui::DragFloat("FOV", &fov, 1.0f, 1.0f, 179.0f))
				{
					cameraComp->SetFov(fov);
				}
			}
		}

		// Mesh (only color for now)
		if (auto* meshComp = obj->GetComponent<MeshComponent>())
		{
			if (ImGui::CollapsingHeader("Mesh Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				// ImGui::TextUnformatted("(Mesh present)");
				glm::vec3 materialColor = meshComp->GetMaterial().get()->GetFloat3Params("color");
				if (ImGui::ColorEdit3("Material Color", &materialColor.x))
				{
					meshComp->GetMaterial().get()->SetFloatParam("color", materialColor);
				}
			}
		}

		// Physics
		if (auto* physicsComp = obj->GetComponent<PhysicsComponent>())
		{
			if (ImGui::CollapsingHeader("Physics Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				RigidBody* body = physicsComp->GetRigidBody().get();

				if (body)
				{
					float mass = body->GetMass();
					if (ImGui::DragFloat(
						"Mass",
						&mass,
						0.1f,
						0.0f,
						1000.0f))
					{
						body->SetMass(mass);
					}

					float friction = body->GetFriction();
					if (ImGui::DragFloat(
						"Friction",
						&friction,
						0.01f,
						0.0f,
						10.0f))
					{
						body->SetFriction(friction);
					}

					static const char* bodyTypes[] =
					{
						"Static",
						"Dynamic",
						"Kinematic"
					};
					int currentType = static_cast<int>(body->GetBodyType());
					if (ImGui::Combo(
						"Body Type",
						&currentType,
						bodyTypes,
						IM_ARRAYSIZE(bodyTypes)))
					{
						body->SetBodyType(
							static_cast<BodyType>(currentType));
					}
				}
			}
		}

		// Animation (Read only for now)
		if (auto* animComp = obj->GetComponent<AnimationComponent>())
		{
			if (ImGui::CollapsingHeader("Animation Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("Animation Component Presents");
			}
		}

		// Audio (Read only for now)
		if (auto* audioComp = obj->GetComponent<AudioComponent>())
		{
			if (ImGui::CollapsingHeader("Audio Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("Audio Component Presents");
			}
		}

		// Audio Listener (Read only for now)
		if (auto* audioListenerComp = obj->GetComponent<AudioListenerComponent>())
		{
			if (ImGui::CollapsingHeader("AudioListener Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("AudioListener Component Presents");
			}
		}
		
		// PlayerController (Read only for now)
		if (auto* playerControllerComp = obj->GetComponent<PlayerControllerComponent>())
		{
			if (ImGui::CollapsingHeader("PlayerController Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				float playerMouseSensitivity = playerControllerComp->GetMouseSensitivity();
				if (ImGui::DragFloat(
					"Mouse Sensitivity",
					&playerMouseSensitivity,
					0.1f,
					0.0f,
					100.0f))
				{
					playerControllerComp->SetMouseSensitivity(playerMouseSensitivity);
				}

				float playerMoveSpeed = playerControllerComp->GetMoveSpeed();
				if (ImGui::DragFloat(
					"Walk Speed",
					&playerMoveSpeed,
					0.01f,
					0.0f,
					100.0f))
				{
					playerControllerComp->SetMoveSpeed(playerMoveSpeed);
				}

				float playerJumpForce = playerControllerComp->GetJumpForce();
				if (ImGui::DragFloat(
					"Jump Force",
					&playerJumpForce,
					0.01f,
					0.0f,
					100.0f))
				{
					playerControllerComp->SetJumpForce(playerJumpForce);
				}
			}
		}
	}

}
