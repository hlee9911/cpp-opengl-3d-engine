#pragma once

#include "Core.h"
#include "Common.h"

#include <glm/vec3.hpp>

namespace eng
{
	class IContactListener;

	enum class CollisionObjectType
	{
		RigidBody,
		KinematicCharacterController
	};

	class CollisionObject
	{
	public:
		CollisionObjectType GetCollisionObjectType() const noexcept { return m_CollisionObjectType; }
		
		void AddContactListener(IContactListener* listener);
		void RemoveContactListener(IContactListener* listener);

	protected:
		void DispatchContactEvent(
			CollisionObject* obj,
			const glm::vec3& pos,
			const glm::vec3& norm);

	protected:
		CollisionObjectType m_CollisionObjectType;
		List<IContactListener*> m_ContactListeners;

		friend class PhysicsManager;
	};

	class IContactListener
	{
	public:
		virtual void OnContact(
			CollisionObject* obj,
			const glm::vec3& pos,
			const glm::vec3& norm) = 0;
	};
}
