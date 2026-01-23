#pragma once;
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

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

	private:
		std::array<bool, 256> m_Keys = { false }; // Simple key state storage
		friend class Engine;
	};
}

#endif // INPUTMANAGER_H
