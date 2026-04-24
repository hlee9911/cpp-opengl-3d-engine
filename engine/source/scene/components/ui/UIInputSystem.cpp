#include "scene/components/ui/UIInputSystem.h"
#include "scene/components/ui/CanvasComponent.h"
#include "Engine.h"

#include <GLFW/glfw3.h>

namespace eng
{
	void UIInputSystem::Update(float deltaTime)
	{
		if (!m_Active || !m_ActiveCanvas) return;

		auto& inputManager = Engine::GetInstance().GetInputManager();
		bool mouseDown = inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
		bool mousePressed = inputManager.WasMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
		bool mouseReleased = inputManager.WasMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT);

		auto mousePos = inputManager.GetMousePositionCurrent();
		// GLFW reports mouse Y from the top left corner, but our UI uses the bottom left corner as the origin, so we need to invert the Y coordinate
		mousePos.y = Engine::GetInstance().GetGraphicsAPI().GetViewport().height - mousePos.y; // Invert Y coordinate for UI
	
		// TODO:
	}

}
