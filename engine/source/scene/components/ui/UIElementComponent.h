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

	protected:
		glm::vec2 m_Pivot = glm::vec2(0.5f);
	};
}
