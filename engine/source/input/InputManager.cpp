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

	void InputManager::SetKeyWasPressed(int key, bool pressed)
	{
		if (key < 0 || key >= static_cast<int>(m_KeyPressed.size())) return;

		m_KeyPressed[key] = pressed;
	}

	bool InputManager::WasKeyPressed(int key) const
	{
		if (key < 0 || key >= static_cast<int>(m_KeyPressed.size())) return false;

		return m_KeyPressed[key];
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

	void InputManager::SetMouseButtonWasPressed(int button, bool pressed)
	{
		if (button < 0 || button >= static_cast<int>(m_MouseKeyPressed.size())) return;

		m_MouseKeyPressed[button] = pressed;
	}

	bool InputManager::WasMouseButtonPressed(int button) const
	{
		if (button < 0 || button >= static_cast<int>(m_MouseKeyPressed.size())) return false;

		return m_MouseKeyPressed[button];
	}

	void InputManager::SetMouseButtonWasReleased(int button, bool released)
	{
		if (button < 0 || button >= static_cast<int>(m_MouseKeyReleased.size())) return;

		m_MouseKeyReleased[button] = released;
	}

	bool InputManager::WasMouseButtonReleased(int button) const
	{
		if (button < 0 || button >= static_cast<int>(m_MouseKeyReleased.size())) return false;

		return m_MouseKeyReleased[button];
	}

	void InputManager::ClearStates()
	{
		m_KeyPressed.fill(false);
		SetMousePositionChanged(false);
		for (auto k : m_MouseKeyPressed)
		{
			SetMouseButtonWasPressed(k, false);
		}
		for (auto k : m_MouseKeyReleased)
		{
			SetMouseButtonWasReleased(k, false);
		}
	}

}
