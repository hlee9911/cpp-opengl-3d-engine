#include "scene/components/ui/UIInputSystem.h"
#include "scene/components/ui/CanvasComponent.h"
#include "scene/components/ui/UIElementComponent.h"
#include "Engine.h"

#include <GLFW/glfw3.h>

namespace eng
{
	void UIInputSystem::Update(float deltaTime)
	{
		if (!m_Active || !m_ActiveCanvas || !m_ActiveCanvas->IsActive()) return;

		auto& inputManager = Engine::GetInstance().GetInputManager();
		bool mouseDown = inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
		bool mousePressed = inputManager.WasMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT);
		bool mouseReleased = inputManager.WasMouseButtonReleased(GLFW_MOUSE_BUTTON_LEFT);

		auto mousePos = inputManager.GetMousePositionCurrent();
		// GLFW reports mouse Y from the top left corner, but our UI uses the bottom left corner as the origin, so we need to invert the Y coordinate
		mousePos.y = Engine::GetInstance().GetGraphicsAPI().GetViewport().height - mousePos.y; // Invert Y coordinate for UI
	
		// TODO:
		UIElementComponent* hit = nullptr;
		auto uiElements = CollectUI(m_ActiveCanvas);
		for (auto element : uiElements)
		{
			if (element->HitTest(mousePos))
			{
				hit = element;
				break;
			}
		}

		// Handle pointer enter/exit events
		if (hit != m_Hovered)
		{
			if (m_Hovered)
			{
				m_Hovered->OnPointerExit();
			}

			m_Hovered = hit;

			if (m_Hovered)
			{
				m_Hovered->OnPointerEnter();
			}

			m_Pressed = nullptr; // reset pressed state when hover changes
		}

		// Handle pointer down/up/click events
		if (!m_Pressed)
		{
			if (mousePressed && m_Hovered)
			{
				m_Pressed = m_Hovered;
				m_Pressed->OnPointerDown();
			}
		}

		if (mouseReleased)
		{
			if (m_Pressed)
			{
				m_Pressed->OnPointerUp();

				if (m_Pressed == m_Hovered)
				{
					m_Pressed->OnPointerClick();
				}
			}

			m_Pressed = nullptr;
		}
	}

	List<UIElementComponent*> UIInputSystem::CollectUI(CanvasComponent* canvas)
	{
		List<UIElementComponent*> result;
		GameObject* canvasObject = canvas->GetOwner();
		const auto& children = canvasObject->GetChildren();

		for (const auto& child : children)
		{
			if (auto component = child->GetComponent<UIElementComponent>())
			{
				// add recursion to collect nested ui elements
				canvas->CollectUI(component, result);
			}
		}
		return result;
	}

}
