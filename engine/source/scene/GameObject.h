#pragma once

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
	class Scene;

	class GameObject
	{
	public:
		virtual ~GameObject() noexcept = default;
		virtual void Init();
		virtual void LoadProperties(const nlohmann::json& json);
		virtual void Update(float deltaTime);
		
		const std::string& GetName() const noexcept;
		void SetName(const std::string& name) noexcept;

		GameObject* GetParent() noexcept;
		bool SetParent(GameObject* parent);

		Scene* GetScene() noexcept { return m_Scene; }

		bool IsAlive() const noexcept;

		void MarkForDestroy();

		void SetActive(bool active) noexcept { m_Active = active; }
		bool IsActive() const noexcept { return m_Active; }

		void AddComponenet(Component* component);
		template<typename T, typename = typename std::enable_if_t<std::is_base_of_v<Component, T>>>
		T* GetComponent()
		{
			size_t typeId = Component::StaticTypeId<T>();

			for (auto& component : m_Components)
			{
				// runtime Id is generated the same wy for every type
				if (component->GetTypeId() == typeId ||
					ComponentFactory::GetInstance().HasParent(component->GetTypeId(), typeId)) // if IDs match, we found the component we want
				{
					return static_cast<T*>(component.get());
				}
			}
			return nullptr;
		}

		GameObject* FindChildByName(const std::string& name);
		const List<unique<GameObject>>& GetChildren() const noexcept { return m_Children; }
		
		const glm::vec3& GetPosition() const noexcept;
		const glm::vec3 GetWorldPosition() const noexcept;
		const glm::vec2 GetPosition2D() const noexcept;
		const glm::vec2 GetWorldPosition2D() const noexcept;
		void SetPosition(const glm::vec3& pos) noexcept;
		void SetWorldPosition(const glm::vec3& pos) noexcept;
		void SetPosition2D(const glm::vec2& pos) noexcept;
		void SetWorldPosition2D(const glm::vec2& pos) noexcept;

		const glm::quat& GetRotation() const noexcept;
		const glm::quat GetWorldRotation() const noexcept;
		const float GetRotation2D() const noexcept;
		void SetRotation(const glm::quat& rot) noexcept;
		void SetWorldRotation(const glm::quat& rot) noexcept;
		void SetRotation2D(float rot) noexcept;

		const glm::vec3& GetScale() const noexcept;
		const glm::vec2& GetScale2D() const noexcept;
		void SetScale(const glm::vec3& scale) noexcept;
		void SetScale2D(const glm::vec2& scale) noexcept;

		const glm::mat4 GetLocalTransform() const noexcept;
		const glm::mat4 GetLocalTransform2D() const noexcept;
		const glm::mat4 GetWorldTransform() const noexcept;
		const glm::mat4 GetWorldTransform2D() const noexcept;

		static GameObject* LoadGLTF(const std::string& path, Scene* gameScene);

	protected:
		GameObject() noexcept = default;

	protected:
		std::string m_Name;
		GameObject* m_Parent = nullptr;
		Scene* m_Scene = nullptr;
		List<unique<GameObject>> m_Children;
		List<unique<Component>> m_Components;
		bool m_IsAlive = true;
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::quat m_Rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
		bool m_Active = true;

		friend class Scene;
	};

	class ObjectCreatorBase
	{
	public:
		virtual ~ObjectCreatorBase() noexcept = default;
		virtual GameObject* CreateGameObject() = 0;
	};

	template<typename T>
	class ObjectCreator : public ObjectCreatorBase
	{
	public:
		virtual GameObject* CreateGameObject() override
		{
			return new T();
		}
	};

	// singleton gameobject factory
	class GameObjectFactory
	{
	public:
		static GameObjectFactory& GetInstance();
		// registerObject like ComponentFactory
		template<typename T>
		void RegisterObject(const std::string& name)
		{
			m_Creators.emplace(name, std::make_unique<ObjectCreator<T>>());
		}

		GameObject* CreateGameObject(const std::string& typeName);

	private:
		Dictionary<std::string, unique<ObjectCreatorBase>> m_Creators;
	};

	// helper macro for registering the game object
#define GAMEOBJECT(ObjectClass) \
public: \
	static void Register() { eng::GameObjectFactory::GetInstance().RegisterObject<ObjectClass>(std::string(#ObjectClass)); } // registers the object type in the factory with its class name as the key
}
