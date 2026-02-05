#include "input/InputManager.h"

namespace eng
{
	void InputManager::SetKeyPressed(int key, bool pressed)
	{
		if (key < 0 || key >= static_cast<int>(m_Keys.size())) return;
		
		m_Keys[key] = pressed;
	}

	bool InputManager::IsKeyPressed(int key) const
	{
		if (key < 0 || key >= static_cast<int>(m_Keys.size())) return false;

		return m_Keys[key];
	}

	void InputManager::SetMouseButtonPressed(int button, bool pressed)
	{
		if (button < 0 || button >= static_cast<int>(m_MouseKeys.size())) return;

		m_MouseKeys[button] = pressed;
	}

	bool InputManager::IsMouseButtonPressed(int button)
	{
		if (button < 0 || button >= static_cast<int>(m_MouseKeys.size())) return false;

		return m_MouseKeys[button];
	}

}
