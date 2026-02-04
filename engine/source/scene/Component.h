#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

namespace eng
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() noexcept = default;
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

#define COMPONENT(ComponentClass) \
public: \
	static size_t TypeId() { return Component::StaticTypeId<ComponentClass>(); } \
	size_t GetTypeId() const override { return TypeId(); }
}

#endif // COMPONENT_H
