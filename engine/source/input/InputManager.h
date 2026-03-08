#pragma once;

#include <glm/vec2.hpp>

#include <array>

namespace eng
{
	class InputManager
	{
	private:
		InputManager() noexcept = default;
		InputManager(const InputManager&) noexcept = delete;
		InputManager(InputManager&&) noexcept = delete;
		InputManager& operator=(const InputManager&) noexcept = delete;
		InputManager& operator=(InputManager&&) noexcept = delete;

	public:
		void SetKeyPressed(int key, bool pressed);
		bool IsKeyPressed(int key) const;

		void SetMouseButtonPressed(int button, bool pressed);
		bool IsMouseButtonPressed(int button);

		void SetMousePositionOld(const glm::vec2& pos) noexcept { m_MousePositionOld = pos; }
		const glm::vec2& GetMousePositionOld() const noexcept { return m_MousePositionOld; }

		void SetMousePositionCurrent(const glm::vec2& pos) noexcept { m_MousePositionCurrent = pos; }
		const glm::vec2& GetMousePositionCurrent() const noexcept { return m_MousePositionCurrent; }
		
		void SetMousePositionChanged(bool changed) noexcept { m_MousePositionChanged = changed; }
		bool IsMousePositionChanged() const noexcept { return m_MousePositionChanged; }

	private:
		std::array<bool, 256> m_Keys = { false }; // Simple key state storage
		std::array<bool, 16> m_MouseKeys = { false };
		glm::vec2 m_MousePositionOld = glm::vec2(0.0f);
		glm::vec2 m_MousePositionCurrent = glm::vec2(0.0f);
		bool m_MousePositionChanged = false;

		friend class Engine;
	};
}
