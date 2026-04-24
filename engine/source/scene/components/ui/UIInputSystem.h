#pragma once

namespace eng
{
	class CanvasComponent;

	class UIInputSystem
	{
	public:
		void SetActive(bool Active) noexcept { m_Active = Active; }
		bool IsActive() const noexcept { return m_Active; }
		void SetActiveCanvas(CanvasComponent* Canvas) noexcept { m_ActiveCanvas = Canvas; }
		void Update(float DeltaTime);

	private:
		bool m_Active = false;
		CanvasComponent* m_ActiveCanvas = nullptr;
	};
}
