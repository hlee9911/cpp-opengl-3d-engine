#pragma once

#include "Core.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace eng
{
	class CanvasComponent;
	class UIElementComponent;

	class UIInputSystem
	{
	public:
		void SetActive(bool Active) noexcept { m_Active = Active; }
		bool IsActive() const noexcept { return m_Active; }
		CanvasComponent* GetActiveCanvas() const noexcept { return m_ActiveCanvas; }
		void SetActiveCanvas(CanvasComponent* Canvas) noexcept { m_ActiveCanvas = Canvas; }
		void Update(float deltaTime);

		List<UIElementComponent*> CollectUI(CanvasComponent* canvas);

	private:
		bool m_Active = false;
		CanvasComponent* m_ActiveCanvas = nullptr;
		UIElementComponent* m_Hovered = nullptr;
		UIElementComponent* m_Pressed = nullptr;
	};
}
