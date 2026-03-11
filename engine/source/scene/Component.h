#pragma once

#include "Core.h"

#include <nlohmann/json.hpp>
#include <cstddef>
#include <string>

namespace eng
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() noexcept = default;
		virtual void LoadProperties(const nlohmann::json& json);
		virtual void Init();
		virtual void Update(float deltaTime) = 0;
		virtual size_t GetTypeId() const = 0;

		GameObject* GetOwner() noexcept { return m_Owner; }

		// each distinct T gets a unique, stable ID
		template<typename T>
		static size_t StaticTypeId()
		{
			static size_t typeId = nextId++;
			return typeId;
		}


	protected:
		GameObject* m_Owner = nullptr;

		friend class GameObject;

	private:
		static size_t nextId; // it generates a unique id for ech component type
	};

	class ComponentCreaterBase
	{
	public:
		virtual ~ComponentCreaterBase() noexcept = default;
		virtual Component* CreateComponent() = 0;
	};

	template<typename T>
	class ComponentCreater : public ComponentCreaterBase
	{
		Component* CreateComponent() override
		{
			return new T();
		}
	};

	class ComponentFactory
	{
	public:
		static ComponentFactory& GetInstance();

		// templated register method for component types
		template<typename T>
		void RegisterComponent(const std::string& name)
		{
			m_Creators.emplace(name, std::make_unique<ComponentCreater<T>>());
		}

		// create component by name, returns nullptr if not found
		Component* CreateComponent(const std::string& name)
		{
			auto it = m_Creators.find(name);
			if (it != m_Creators.end())
			{
				return it->second->CreateComponent();
			}
			return nullptr;
		}

	private:
		Dictionary<std::string, unique<ComponentCreaterBase>> m_Creators;
	};

#define COMPONENT(ComponentClass) \
public: \
	static size_t TypeId() { return eng::Component::StaticTypeId<ComponentClass>(); } \
	size_t GetTypeId() const override { return TypeId(); } \
	static void Register() { eng::ComponentFactory::GetInstance().RegisterComponent<ComponentClass>(std::string(#ComponentClass)); } // registers the component type in the factory with its class name as the key
}
