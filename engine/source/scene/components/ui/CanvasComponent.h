#pragma once

#include "scene/Component.h"

namespace eng
{
	class UIElementComponent;
	class CanvasComponent : public Component
	{
		COMPONENT(CanvasComponent)

	public:
		void Update(float deltaTime) override;
		void Render(UIElementComponent* element);

	};
}
