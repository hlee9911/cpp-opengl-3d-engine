#pragma once

#include "scene/Component.h"
#include "physics/RigidBody.h"
#include "Core.h"

namespace eng
{
	/// <summary>
	/// PhysicsComponent is responsible for synchronizing a GameObject's transform with a RigidBody in the physics simulation. 
	/// It updates the RigidBody's position and rotation based on the GameObject's transform during initialization, 
	/// and then continuously updates the GameObject's transform based on the RigidBody's state during each update cycle. 
	/// This allows for realistic physics interactions while keeping the GameObject's transform in sync with the physics simulation.
	/// </summary>
	class PhysicsComponent : public Component
	{
		COMPONENT(PhysicsComponent)

	public:
		PhysicsComponent() noexcept = default;
		PhysicsComponent(const shared<RigidBody>& body) noexcept;

		void Init() override;
		void Update(float deltaTime) override;

		void SetRigidBody(const shared<RigidBody>& body) noexcept { m_RigidBody = body; }

	private:
		shared<RigidBody> m_RigidBody;
	};
}