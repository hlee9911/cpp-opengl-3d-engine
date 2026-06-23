#include "physics/PhysicsManager.h"
#include "physics/RigidBody.h"
#include "physics/CollisionObject.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace eng
{
	PhysicsManager::PhysicsManager() noexcept
	{

	}

	PhysicsManager::~PhysicsManager() noexcept
	{

	}

	void PhysicsManager::Init()
	{
		m_Broadphase = std::make_unique<btDbvtBroadphase>();
		m_CollisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
		m_Dispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfig.get());
		m_Solver = std::make_unique<btSequentialImpulseConstraintSolver>();
		m_World = std::make_unique<btDiscreteDynamicsWorld>(
			m_Dispatcher.get(), 
			m_Broadphase.get(), 
			m_Solver.get(), 
			m_CollisionConfig.get()
		);

		m_World->setGravity(btVector3(0, m_Gravity, 0));
	}

	void PhysicsManager::Update(float deltaTime)
	{
		const btScalar fixedTimeStep = 1.0f / 60.0f;
		const int maxSubsteps = 4;
		m_World->stepSimulation(deltaTime, maxSubsteps, fixedTimeStep);
		
		// collision
		// plan:
		// get Collision manifolds
		// extract both bodies
		// cast userPointer to CollisionObject* then read the contact position/normal
		// and notify listeners

		// process collisions
		auto dispatcher = m_World->getDispatcher();
		const auto numManifolds = dispatcher->getNumManifolds();
		for (int i = 0; i < numManifolds; ++i)
		{
			// get the manifold
			auto manifold = dispatcher->getManifoldByIndexInternal(i);
			if (!manifold)
			{
				continue;
			}

			// get the collision objects from the manifold and cast their user pointers to CollisionObject*
			auto bodyA = reinterpret_cast<CollisionObject*>(manifold->getBody0()->getUserPointer());
			auto bodyB = reinterpret_cast<CollisionObject*>(manifold->getBody1()->getUserPointer());

			// For player applying force to dynamic objects
			//auto btA = manifold->getBody0();
			//auto btB = manifold->getBody1();

			//btRigidBody* rbA = const_cast<btRigidBody*>(
			//	btRigidBody::upcast(btA)
			//);
			//btRigidBody* rbB = const_cast<btRigidBody*>(
			//	btRigidBody::upcast(btB)
			//);

			//bool aIsCharacter = btA->getCollisionFlags() & btCollisionObject::CF_CHARACTER_OBJECT;
			//bool bIsCharacter = btB->getCollisionFlags() & btCollisionObject::CF_CHARACTER_OBJECT;

			//if (aIsCharacter && rbB)
			//{
			//	if (!rbB->isStaticObject() && !rbB->isKinematicObject())
			//		rbB->activate(true);

			//	ApplyPlayerPush(rbB, btA, btB);
			//}
			//if (bIsCharacter && rbA)
			//{
			//	if (!rbA->isStaticObject() && !rbA->isKinematicObject())
			//		rbA->activate(true);

			//	ApplyPlayerPush(rbA, btB, btA);
			//}

			if (!bodyA || !bodyB)
			{
				continue;
			}

			// get the number of contacts in the manifold
			const auto numContacts = manifold->getNumContacts();
			for (int j = 0; j < numContacts; ++j)
			{
				const auto& point = manifold->getContactPoint(j);
				const glm::vec3 pos(
					point.m_positionWorldOnB.x(),
					point.m_positionWorldOnB.y(),
					point.m_positionWorldOnB.z()
				);
				const glm::vec3 norm(
					point.m_normalWorldOnB.x(),
					point.m_normalWorldOnB.y(),
					point.m_normalWorldOnB.z()
				);

				// dispatch contact events to both bodies
				bodyA->DispatchContactEvent(bodyB, pos, norm);
				bodyB->DispatchContactEvent(bodyA, pos, norm);
			}
		}
	}

	void PhysicsManager::AddRigidBody(RigidBody* body)
	{
		if (!body || !m_World) return;

		if (auto rigidBody = body->GetBody())
		{
			// add the rigid body to the physics world with appropriate collision filters
			/*m_World->addRigidBody(rigidBody,
				btBroadphaseProxy::StaticFilter,
				btBroadphaseProxy::AllFilter);*/

			short group = btBroadphaseProxy::DefaultFilter;

			// set static objects to static fillter
			if (body->GetBodyType() == BodyType::Static)
			{
				group = btBroadphaseProxy::StaticFilter;
			}

			m_World->addRigidBody(
				rigidBody,
				group,
				btBroadphaseProxy::AllFilter);

			body->SetAddedToWorld(true);

			WakeUpNearbyCollidingRigidBodies();
		}
	}

	void PhysicsManager::RemoveRigidBody(RigidBody* body)
	{
		if (!body || !m_World) return;

		if (auto rigidBody = body->GetBody())
		{
			// remove the rigid body from the physics world
			m_World->removeRigidBody(rigidBody);
			body->SetAddedToWorld(false);
			WakeUpNearbyCollidingRigidBodies();
		}
	}

	void PhysicsManager::ApplyPlayerPush(
		btRigidBody* body,
		const btCollisionObject* playerObj,
		const btCollisionObject* otherObj)
	{
		if (!body) return;

		if (body->isStaticObject() || body->isKinematicObject()) return;

		// keep body awake during interaction
		body->activate(true);
		body->setActivationState(DISABLE_DEACTIVATION);

		btTransform playerT = playerObj->getWorldTransform();
		btTransform objectT = otherObj->getWorldTransform();

		btVector3 playerPos = playerT.getOrigin();
		btVector3 objectPos = objectT.getOrigin();

		btVector3 dir = objectPos - playerPos;
		dir.setY(0);

		if (dir.length2() < 0.0001f) return;

		dir.normalize();

		float invMass = body->getInvMass();
		if (invMass <= 0.0f) return; // safe guard

		float mass = 1.0f / invMass;

		float strength = 4.0f / mass;
		strength = std::min(strength, 30.0f);

		btVector3 impulse = dir * strength;

		body->applyCentralImpulse(impulse);
	}

	void PhysicsManager::WakeUpNearbyCollidingRigidBodies()
	{
		// wake up other non static rigid bodies that are colliding with this object
		for (int i = 0; i < m_World->getNumCollisionObjects(); i++)
		{
			auto obj = m_World->getCollisionObjectArray()[i];

			btRigidBody* body = btRigidBody::upcast(obj);

			if (body && !body->isStaticObject())
			{
				body->activate(true);
			}
		}
	}

	btDiscreteDynamicsWorld* PhysicsManager::GetWorld()
	{
		return m_World.get();
	}

}
