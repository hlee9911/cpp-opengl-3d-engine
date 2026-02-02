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

		GameObject* GetOwner() noexcept { return m_Owner; }

	protected:
		GameObject* m_Owner = nullptr;

		friend class GameObject;
	};
}

#endif // COMPONENT_H
