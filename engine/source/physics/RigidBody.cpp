#include "physics/RigidBody.h"
#include "Engine.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace eng
{
	RigidBody::RigidBody(BodyType type, const shared<Collider>& collider, float mass, float friction) noexcept
		: m_BodyType{ type },
		m_Collider{ collider },
		m_Mass{ mass },
		m_Friction{ friction }
	{
		if (!collider) return;
		
		btVector3 inertia(0, 0, 0);
		if (m_BodyType == BodyType::Dynamic && mass > 0.0f && m_Collider->GetShape())
		{
			// calculate inertia for dynamic bodies
			m_Collider->GetShape()->calculateLocalInertia(btScalar(mass), inertia);
		}

		btTransform transform;
		transform.setIdentity();
		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		btRigidBody::btRigidBodyConstructionInfo info(
			(m_BodyType == BodyType::Dynamic) ? btScalar(mass) : btScalar(0),
			motionState,
			m_Collider->GetShape(),
			inertia
		);

		m_Body = std::make_unique<btRigidBody>(info);
		m_Body->setFriction(friction);

		if (m_BodyType == BodyType::Kinematic)
		{
			// set kinematic flag and disable deactivation for kinematic bodies
			m_Body->setCollisionFlags(m_Body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			m_Body->setActivationState(DISABLE_DEACTIVATION);
		}
	}

	RigidBody::~RigidBody() noexcept
	{
		if (m_AddedToWorld)
		{
			Engine::GetInstance().GetPhysicsManager().RemoveRigidBody(this);
		}
	}

	void RigidBody::SetPosition(const glm::vec3& position)
	{
		if (!m_Body) return;

		auto& tr = m_Body->getWorldTransform();
		// set the origin (position) of the transform, keeping the current rotation
		tr.setOrigin(btVector3(btScalar(position.x), btScalar(position.y), btScalar(position.z)));
		if (m_Body->getMotionState())
		{
			// also update the motion state to keep it in sync with the new position
			m_Body->getMotionState()->setWorldTransform(tr);
		}
		m_Body->setWorldTransform(tr);
	}

	glm::vec3 RigidBody::GetPosition() const
	{
		const auto& pos = m_Body->getWorldTransform().getOrigin();
		return glm::vec3(pos.x(), pos.y(), pos.z());
	}

	void RigidBody::SetRotation(const glm::quat& rotation)
	{
		if (!m_Body) return;

		auto& tr = m_Body->getWorldTransform();
		// set the rotation of the transform, keeping the current position
		tr.setRotation(btQuaternion(btScalar(rotation.x), btScalar(rotation.y), btScalar(rotation.z), btScalar(rotation.w)));
		if (m_Body->getMotionState())
		{
			// also update the motion state to keep it in sync with the new rotation
			m_Body->getMotionState()->setWorldTransform(tr);
		}
		m_Body->setWorldTransform(tr);
	}

	glm::quat RigidBody::GetRotation() const
	{
		const auto& rot = m_Body->getWorldTransform().getRotation();
		return glm::quat(rot.w(), rot.x(), rot.y(), rot.z());
	}
}
