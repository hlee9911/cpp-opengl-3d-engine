#pragma once

#include "Core.h"

namespace eng
{
	class CanvasComponent;
	class UIElementComponent;

	class UIInputSystem
	{
	public:
		void SetActive(bool Active) noexcept { m_Active = Active; }
		bool IsActive() const noexcept { return m_Active; }
		void SetActiveCanvas(CanvasComponent* Canvas) noexcept { m_ActiveCanvas = Canvas; }
		void Update(float DeltaTime);

		List<UIElementComponent*> CollectUI(CanvasComponent* canvas);

	private:
		bool m_Active = false;
		CanvasComponent* m_ActiveCanvas = nullptr;
		UIElementComponent* m_Hovered = nullptr;
		UIElementComponent* m_Pressed = nullptr;
	};
}
