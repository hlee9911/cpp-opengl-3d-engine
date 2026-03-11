#include "scene/components/PhysicsComponent.h"
#include "scene/GameObject.h"
#include "Engine.h"

namespace eng
{
	PhysicsComponent::PhysicsComponent(const shared<RigidBody>& body) noexcept
		: m_RigidBody{ body }
	{

	}

	void PhysicsComponent::Init()
	{
		if (!m_RigidBody) return;

		// sync the RigidBody's transform with the GameObject's transform
		const auto pos = m_Owner->GetWorldPosition();
		const auto rot = m_Owner->GetWorldRotation();

		m_RigidBody->SetPosition(pos);
		m_RigidBody->SetRotation(rot);

		Engine::GetInstance().GetPhysicsManager().AddRigidBody(m_RigidBody.get());
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		if (!m_RigidBody) return;

		// sync the GameObject's transform with the RigidBody's transform
		if (m_RigidBody->GetBodyType() == BodyType::Dynamic)
		{
			m_Owner->SetWorldPosition(m_RigidBody->GetPosition());
			m_Owner->SetWorldRotation(m_RigidBody->GetRotation());
		}
	}
}
