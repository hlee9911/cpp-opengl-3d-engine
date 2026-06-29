#pragma once

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

class btRigidBody;
class btCollisionObject;

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

		void ApplyPlayerPush(btRigidBody* body, const btCollisionObject* playerObj, const btCollisionObject* otherObj);
		void WakeUpNearbyCollidingRigidBodies();

		btDiscreteDynamicsWorld* GetWorld();

		const float GetGravity() const noexcept { return m_Gravity; }

	private:
		unique<btBroadphaseInterface> m_Broadphase;
		unique<btDefaultCollisionConfiguration> m_CollisionConfig;
		unique<btCollisionDispatcher> m_Dispatcher;
		unique<btSequentialImpulseConstraintSolver> m_Solver;
		unique<btDiscreteDynamicsWorld> m_World;

		const float m_Gravity = -9.81f;
	};
}
