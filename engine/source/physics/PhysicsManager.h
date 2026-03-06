#pragma once

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

#include "Core.h"

namespace eng
{
	class RigidBody;

	class PhysicsManager
	{
	public:
		PhysicsManager() noexcept;
		~PhysicsManager() noexcept;
		
		void Init();
		void Update(float deltaTime);

		void AddRigidBody(RigidBody* body);
		void RemoveRigidBody(RigidBody* body);

		btDiscreteDynamicsWorld* GetWorld();

	private:
		unique<btBroadphaseInterface> m_Broadphase;
		unique<btDefaultCollisionConfiguration> m_CollisionConfig;
		unique<btCollisionDispatcher> m_Dispatcher;
		unique<btSequentialImpulseConstraintSolver> m_Solver;
		unique<btDiscreteDynamicsWorld> m_World;
	};
}
