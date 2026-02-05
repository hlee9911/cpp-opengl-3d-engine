#include "scene/GameObject.h"

#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	void GameObject::Update(float deltaTime)
	{
		for (auto& component : m_Components)
		{
			component->Update(deltaTime);
		}

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

	void GameObject::AddComponenet(Component* component)
	{
		m_Components.emplace_back(component);
		component->m_Owner = this;
	}

	const glm::vec3& GameObject::GetPosition() const noexcept
	{
		return m_Position;
	}

	void GameObject::SetPosition(const glm::vec3& pos) noexcept
	{
		m_Position = pos;
	}

	const glm::quat& GameObject::GetRotation() const noexcept
	{
		return m_Rotation;
	}

	void GameObject::SetRotation(const glm::quat& rot) noexcept
	{
		m_Rotation = rot;
	}

	const glm::vec3& GameObject::GetScale() const noexcept
	{
		return m_Scale;
	}

	void GameObject::SetScale(const glm::vec3& scale) noexcept
	{
		m_Scale = scale;
	}

	glm::mat4 GameObject::GetLocalTransform() const
	{
		// identity matrix
		glm::mat4 mat = glm::mat4(1.0f);

		// Translation
		mat = glm::translate(mat, m_Position);

		// Rotation
		//mat = glm::rotate(mat, m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
		//mat = glm::rotate(mat, m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
		//mat = glm::rotate(mat, m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis
		// Use single entity called quaternion instead of three different angles
		mat = mat * glm::mat4_cast(m_Rotation);

		// Scale
		mat = glm::scale(mat, m_Scale);
		
		return mat;
	}

	glm::mat4 GameObject::GetWorldTransform() const
	{
		if (m_Parent)
		{
			return m_Parent->GetWorldTransform() * GetLocalTransform();
		}
		return GetLocalTransform();
	}
}
