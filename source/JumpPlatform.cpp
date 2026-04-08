#include "JumpPlatform.h"

void JumpPlatform::Init()
{
	// add this object as a contact listener to its physics component so we can detect when the player jumps on it
	auto physics = GetComponent<eng::PhysicsComponent>();
	if (physics)
	{
		auto rigidBody = physics->GetRigidBody();
		if (rigidBody)
		{
			rigidBody->AddContactListener(this);
		}
	}
}

void JumpPlatform::OnContact(
	eng::CollisionObject* obj,
	const glm::vec3& pos,
	const glm::vec3& norm)
{
	// check if the object that collided with this platform is the player character controller. 
	// if it is, we can apply an upward impulse to make the player jump
	if (obj->GetCollisionObjectType() == eng::CollisionObjectType::KinematicCharacterController)
	{
		auto controller = static_cast<eng::KinematicCharacterController*>(obj);
		if (controller)
		{
			// apply an upward impulse to the character controller to make it jump
			controller->Jump(glm::vec3(0.0f, 20.0f, 0.0f));
		}
	}
}
