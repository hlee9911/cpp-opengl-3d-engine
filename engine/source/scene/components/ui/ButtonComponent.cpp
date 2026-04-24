#include "scene/components/ui/ButtonComponent.h"
#include "scene/components/ui/CanvasComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void ButtonComponent::Render(CanvasComponent* canvas)
	{
		if (!canvas) return;

		auto pos = m_Owner->GetWorldPosition2D();
		pos.x -= m_Rect.x * m_Pivot.x;
		pos.y -= m_Rect.y * m_Pivot.y;

		canvas->DrawRect(
			pos,
			pos + m_Rect,
			*m_CurrentColor
		);
	}

	bool ButtonComponent::HitTest(const glm::vec2& pos) const
	{
		// Get the world position of the owner and calculate the button's bounding box
		auto ownerPos = m_Owner->GetWorldPosition2D();
		float x1 = ownerPos.x - m_Rect.x * m_Pivot.x;
		float y1 = ownerPos.y - m_Rect.y * m_Pivot.y;
		float x2 = x1 + m_Rect.x;
		float y2 = y1 + m_Rect.y;

		// Check if the input position is within the bounding box
		return (x1 <= pos.x && x2 >= pos.x && y1 <= pos.y && y2 >= pos.y);
	}

	void ButtonComponent::OnPointerEnter()
	{
		m_CurrentColor = &m_HoveredColor;
	}

	void ButtonComponent::OnPointerExit()
	{
		m_CurrentColor = &m_Color;
	}

	void ButtonComponent::OnPointerUp()
	{
		m_CurrentColor = &m_HoveredColor;
	}

	void ButtonComponent::OnPointerDown()
	{
		m_CurrentColor = &m_PressedColor;
	}

	void ButtonComponent::OnPointerClick()
	{
		if (onClick)
		{
			onClick();
		}
	}

}
