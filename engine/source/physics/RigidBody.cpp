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

		m_CollisionObjectType = CollisionObjectType::RigidBody;
		
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
		
		// set user pointer to this CollisionObject for collision callbacks
		m_Body->setUserPointer(this);

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

	void RigidBody::SetMass(float mass)
	{
		if (!m_Body) return;

		m_Mass = mass;

		btVector3 inertia(0, 0, 0);

		if (m_BodyType == BodyType::Dynamic &&
			m_Mass > 0.0f &&
			m_Collider &&
			m_Collider->GetShape())
		{
			m_Collider->GetShape()->calculateLocalInertia(
				btScalar(m_Mass),
				inertia);
		}

		m_Body->setMassProps(
			(m_BodyType == BodyType::Dynamic) ? btScalar(m_Mass) : btScalar(0.0f),
			inertia);

		m_Body->updateInertiaTensor();
		m_Body->activate(true);
	}

	void RigidBody::SetFriction(float friction)
	{
		if (!m_Body) return;

		m_Friction = friction;

		m_Body->setFriction(btScalar(friction));
	}

	void RigidBody::SetBodyType(BodyType type)
	{
		if (!m_Body) return;

		m_BodyType = type;

		int flags = m_Body->getCollisionFlags();

		flags &= ~btCollisionObject::CF_KINEMATIC_OBJECT;

		switch (type)
		{
			case BodyType::Static:
			{
				m_Body->setMassProps(0.0f, btVector3(0, 0, 0));
				break;
			}
			case BodyType::Dynamic:
			{
				btVector3 inertia(0, 0, 0);

				if (m_Collider && m_Collider->GetShape())
				{
					m_Collider->GetShape()->calculateLocalInertia(
						btScalar(m_Mass),
						inertia);
				}

				m_Body->setMassProps(
					btScalar(m_Mass),
					inertia);

				break;
			}
			case BodyType::Kinematic:
			{
				m_Body->setMassProps(0.0f, btVector3(0, 0, 0));

				flags |= btCollisionObject::CF_KINEMATIC_OBJECT;

				m_Body->setActivationState(DISABLE_DEACTIVATION);

				break;
			}
		}

		m_Body->setCollisionFlags(flags);
		m_Body->activate(true);
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

		// wake the body so the physics simulation updates immediately
		m_Body->activate(true);
	}

	glm::vec3 RigidBody::GetPosition() const
	{
		if (!m_Body) return glm::vec3(0.0f);

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

		// wake the body so the physics simulation updates immediately
		m_Body->activate(true);
	}

	glm::quat RigidBody::GetRotation() const
	{
		if (!m_Body) return glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

		const auto& rot = m_Body->getWorldTransform().getRotation();
		return glm::quat(rot.w(), rot.x(), rot.y(), rot.z());
	}

	void RigidBody::SetScale(const glm::vec3& scale)
	{
		if (!m_Body || !m_Collider || !m_Collider->GetShape()) return;

		// scale is applied directly to the collision shape
		m_Collider->GetShape()->setLocalScaling(
			btVector3(
				btScalar(scale.x),
				btScalar(scale.y),
				btScalar(scale.z)));

		// if this is a dynamic rigid body, changing the shape size
		// changes its inertia tensor, so we need to recalculate it
		if (m_BodyType == BodyType::Dynamic && m_Mass > 0.0f)
		{
			btVector3 inertia(0, 0, 0);

			m_Collider->GetShape()->calculateLocalInertia(
				btScalar(m_Mass),
				inertia);

			m_Body->setMassProps(
				btScalar(m_Mass),
				inertia);

			m_Body->updateInertiaTensor();
		}

		// wake the body so the physics simulation updates immediately
		m_Body->activate(true);
	}

	glm::vec3 RigidBody::GetScale() const
	{
		if (!m_Body || !m_Collider || !m_Collider->GetShape()) return glm::vec3(1.0f);

		// retrieve the collision shape's local scaling
		const btVector3 scale =
			m_Collider->GetShape()->getLocalScaling();

		return glm::vec3(
			scale.x(),
			scale.y(),
			scale.z());
	}
	
	/// <summary>
	/// Applies an impulse to the rigid body, which is a sudden force that changes its velocity immediately. 
	/// The impulse is applied at the center of mass of the body
	/// </summary>
	/// <param name="impulse"></param>
	void RigidBody::ApplyImpulse(const glm::vec3& impulse)
	{
		if (!m_Body) return;

		m_Body->applyCentralImpulse(btVector3(
			btScalar(impulse.x), 
			btScalar(impulse.y),
			btScalar(impulse.z)
		));
	}
}
