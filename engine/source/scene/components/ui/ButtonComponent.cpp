#include "scene/components/ui/ButtonComponent.h"
#include "scene/components/ui/CanvasComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void ButtonComponent::LoadProperties(const nlohmann::json& json)
	{
		if (json.contains("rect"))
		{
			auto& rectObj = json["rect"];
			SetRect(glm::vec2(
				rectObj.value("x", 1.0f),
				rectObj.value("y", 1.0f)
			));
		}

		if (json.contains("color"))
		{
			auto& colorObj = json["color"];
			SetColor(glm::vec4(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f),
				colorObj.value("a", 1.0f)
			));
		}

		if (json.contains("hovered"))
		{
			auto& colorObj = json["hovered"];
			SetHoveredColor(glm::vec4(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f),
				colorObj.value("a", 1.0f)
			));
		}

		if (json.contains("pressed"))
		{
			auto& colorObj = json["pressed"];
			SetPressedColor(glm::vec4(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f),
				colorObj.value("a", 1.0f)
			));
		}
	}

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
