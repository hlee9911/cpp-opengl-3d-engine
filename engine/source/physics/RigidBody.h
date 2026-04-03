#pragma once

#include "physics/Collider.h"
#include "Core.h"

#include <glm/gtc/quaternion.hpp>

class btRigidBody;

namespace eng
{
	enum class BodyType
	{
		Static,
		Dynamic,
		Kinematic
	};

	/// <summary>
	/// Represents a rigid body in the physics simulation. It encapsulates a Bullet btRigidBody and provides an interface for setting its properties and synchronizing its transform with a GameObject.
	/// </summary>
	class RigidBody
	{
	public:
		RigidBody(BodyType type, const shared<Collider>& collider, float mass, float friction) noexcept;
		~RigidBody() noexcept;
		btRigidBody* GetBody() const noexcept { return m_Body.get(); }
		void SetAddedToWorld(bool added) noexcept { m_AddedToWorld = added; }
		bool IsAddedToWorld() const noexcept { return m_AddedToWorld; }

		BodyType GetBodyType() const noexcept { return m_BodyType; }

		void SetPosition(const glm::vec3& position);
		glm::vec3 GetPosition() const;
		void SetRotation(const glm::quat& rotation);
		glm::quat GetRotation() const;

		void ApplyImpulse(const glm::vec3& impulse);

	private:
		unique<btRigidBody> m_Body;
		BodyType m_BodyType = BodyType::Static; 
		shared<Collider> m_Collider;
		float m_Mass = 0.0f;
		float m_Friction = 0.5f;
		bool m_AddedToWorld = false;
	};
}
