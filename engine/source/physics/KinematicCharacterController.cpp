#include "physics/KinematicCharacterController.h"
#include "Engine.h"

#include <btBulletDynamicsCommon.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace eng
{
	KinematicCharacterController::KinematicCharacterController(float radius, float height) noexcept
		: m_Radius{ radius },
		m_Height{ height }
	{
		auto world = Engine::GetInstance().GetPhysicsManager().GetWorld();

		auto capsule = new btCapsuleShape(m_Radius, m_Height);

		m_Ghost = std::make_unique<btPairCachingGhostObject>();
		btTransform start;
		start.setIdentity();
		start.setOrigin(btVector3(0.0f, 2.0f, 0.0f));
		m_Ghost->setWorldTransform(start);
		m_Ghost->setCollisionShape(capsule);
		m_Ghost->setCollisionFlags(m_Ghost->getCollisionFlags() | btCollisionObject::CF_CHARACTER_OBJECT);
	
		world->getBroadphase()->getOverlappingPairCache()->
			setInternalGhostPairCallback(new btGhostPairCallback());

		const btScalar stepHeight = btScalar(0.35f); // how high the character can step up
		m_Controller = std::make_unique<btKinematicCharacterController>(m_Ghost.get(), capsule, stepHeight);
	
		m_Controller->setMaxSlope(btRadians(50.0f)); // maximum slope the character can walk up
		m_Controller->setGravity(world->getGravity()); // set gravity for the character controller, negative values is downwards, positive values is upwards
	
		// Add the ghost object to the world, so it can interact with other objects
		world->addCollisionObject(
			m_Ghost.get(),
		    btBroadphaseProxy::CharacterFilter,
			btBroadphaseProxy::AllFilter & ~btBroadphaseProxy::SensorTrigger); // collide with most things
		world->addAction(m_Controller.get());
	}

	KinematicCharacterController::~KinematicCharacterController() noexcept
	{
		auto world = Engine::GetInstance().GetPhysicsManager().GetWorld();
		if (m_Controller)
		{
			world->removeAction(m_Controller.get());
		}

		if (m_Ghost)
		{
			world->removeCollisionObject(m_Ghost.get());
		}
	}

	glm::vec3 KinematicCharacterController::GetPosition() const
	{
		const auto& pos = m_Ghost->getWorldTransform().getOrigin();
		// offset the camera by m_Height * 0.5f + m_Radius, so the camera is at the center of the character
		const glm::vec3 offset(0.0f, m_Height * 0.5f + m_Radius, 0.0f);
		return glm::vec3(pos.x(), pos.y(), pos.z()) + offset;
	}

	glm::vec3 KinematicCharacterController::GetRotation() const
	{
		const auto& rot = m_Ghost->getWorldTransform().getRotation();
		return glm::vec3(rot.x(), rot.y(), rot.z());
	}

	void KinematicCharacterController::Walk(const glm::vec3& direction)
	{
		m_Controller->setWalkDirection(btVector3(
			btScalar(direction.x),
			btScalar(direction.y),
			btScalar(direction.z)
		));
	}

	void KinematicCharacterController::Jump(const glm::vec3& direction)
	{
		if (m_Controller->onGround())
		{
			m_Controller->jump(btVector3(
				btScalar(direction.x),
				btScalar(direction.y),
				btScalar(direction.z)
			));
		}
	}

	bool KinematicCharacterController::IsOnGround() const
	{
		return m_Controller->onGround();
	}
}
