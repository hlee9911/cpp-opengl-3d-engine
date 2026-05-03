#include "scene/components/ui/UIElementComponent.h"

namespace eng
{
	void UIElementComponent::Render(CanvasComponent* canvas)
	{

	}

	// Checks if the cursor is inside the UI element's bounds
	// Thats how we know the element is hit
	bool UIElementComponent::HitTest(const glm::vec2& pos)
	{
		return false;
	}

	void UIElementComponent::OnPointerEnter()
	{

	}

	void UIElementComponent::OnPointerExit()
	{

	}

	void UIElementComponent::OnPointerUp()
	{

	}

	void UIElementComponent::OnPointerDown()
	{

	}

	void UIElementComponent::OnPointerClick()
	{

	}

}
