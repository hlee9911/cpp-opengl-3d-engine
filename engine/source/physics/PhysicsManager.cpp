#include "physics/PhysicsManager.h"
#include "physics/RigidBody.h"

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

		m_World->setGravity(btVector3(0, -9.81f, 0));
	}

	void PhysicsManager::Update(float deltaTime)
	{
		const btScalar fixedTimeStep = 1.0f / 60.0f;
		const int maxSubsteps = 4;
		m_World->stepSimulation(deltaTime, maxSubsteps, fixedTimeStep);
	}

	void PhysicsManager::AddRigidBody(RigidBody* body)
	{
		if (!body || !m_World) return;

		if (auto rigidBody = body->GetBody())
		{
			// add the rigid body to the physics world with appropriate collision filters
			m_World->addRigidBody(rigidBody,
				btBroadphaseProxy::StaticFilter,
				btBroadphaseProxy::AllFilter);
			body->SetAddedToWorld(true);
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
		}
	}

	btDiscreteDynamicsWorld* PhysicsManager::GetWorld()
	{
		return m_World.get();
	}

}
