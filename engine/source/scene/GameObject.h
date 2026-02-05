#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "scene/Component.h"
#include "Core.h"

#include <string>
#include <vector>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

namespace eng
{
	class GameObject
	{
	public:
		virtual ~GameObject() noexcept = default;
		virtual void Update(float deltaTime);
		
		const std::string& GetName() const noexcept;
		void SetName(const std::string& name) noexcept;

		GameObject* GetParent() noexcept;
		bool IsAlive() const noexcept;

		void MarkForDestroy();

		void AddComponenet(Component* component);
		template<typename T, typename = typename std::enable_if_t<std::is_base_of_v<Component, T>>>
		T* GetComponent()
		{
			size_t typeId = Component::StaticTypeId<T>();

			for (auto& component : m_Components)
			{
				// runtime Id is generated the same wy for every type
				if (component->GetTypeId() == typeId) // if IDs match, we found the component we want
				{
					return static_cast<T*>(component.get());
				}
			}
			return nullptr;
		}

		const glm::vec3& GetPosition() const noexcept;
		void SetPosition(const glm::vec3& pos) noexcept;

		const glm::quat& GetRotation() const noexcept;
		void SetRotation(const glm::quat& rot) noexcept;

		const glm::vec3& GetScale() const noexcept;
		void SetScale(const glm::vec3& scale) noexcept;

		glm::mat4 GetLocalTransform() const;
		glm::mat4 GetWorldTransform() const;

	protected:
		GameObject() noexcept = default;

	private:
		std::string m_Name;
		GameObject* m_Parent = nullptr;
		std::vector<std::unique_ptr<GameObject>> m_Children;
		List<unique<Component>> m_Components;
		bool m_IsAlive = true;
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);

		friend class Scene;
	};
}

#endif // GAMEOBJECT_H
