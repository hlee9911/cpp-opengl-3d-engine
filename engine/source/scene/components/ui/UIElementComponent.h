#pragma once

#include "scene/Component.h"

#include <glm/vec2.hpp>

namespace eng
{
	class CanvasComponent;

	class UIElementComponent : public Component
	{
		COMPONENT(UIElementComponent)

	public:
		virtual void Render(CanvasComponent* canvas);
		virtual bool HitTest(const glm::vec2& pos);
		virtual void OnPointerEnter();
		virtual void OnPointerExit();
		virtual void OnPointerUp();
		virtual void OnPointerDown();
		virtual void OnPointerClick();

	//protected:
	//	glm::vec2 m_Pivot = glm::vec2(0.5f);
	};
}
