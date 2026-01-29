#include "scene/GameObject.h"

namespace eng
{
	void GameObject::Update(float deltaTime)
	{
		for (auto it = m_Children.begin(); it != m_Children.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = m_Children.erase(it);
			}
		}
	}

	const std::string& GameObject::GetName() const noexcept
	{
		return m_Name;
	}

	void GameObject::SetName(const std::string& name) noexcept
	{
		m_Name = name;
	}

	GameObject* GameObject::GetParent() noexcept
	{
		return m_Parent;
	}

	bool GameObject::IsAlive() const noexcept
	{
		return m_IsAlive;
	}

	void GameObject::MarkForDestroy()
	{
		m_IsAlive = false;
	}
}
