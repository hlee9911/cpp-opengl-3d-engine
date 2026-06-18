#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "physics/CollisionObject.h"
#include "Core.h"

class btPairCachingGhostObject;
class btKinematicCharacterController;

namespace eng
{
	// A kinematic character controller is a special type of physics object that is not affected by forces or collisions, but can still interact with the environment. 
	// It is typically used for player characters in games, as it allows for smooth movement and precise control. The character controller is implemented using a ghost object
	class KinematicCharacterController : public CollisionObject
	{
	public:
		KinematicCharacterController(float radius, float height, const glm::vec3& position) noexcept;
		~KinematicCharacterController() noexcept;

		glm::vec3 GetPosition() const;
		glm::vec3 GetRotation() const;

		void SetPosition(const glm::vec3& pos);
		void Walk(const glm::vec3& direction);
		void Jump(const glm::vec3& direction);
		bool IsOnGround() const;

	private:
		float m_Height = 0.0f;
		float m_Radius = 0.0f;

		unique<btPairCachingGhostObject> m_Ghost;
		unique<btKinematicCharacterController> m_Controller;
	};
}
