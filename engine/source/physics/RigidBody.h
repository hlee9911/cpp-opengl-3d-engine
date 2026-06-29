#pragma once

#include "physics/Collider.h"
#include "physics/CollisionObject.h"
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
	class RigidBody : public CollisionObject
	{
	public:
		RigidBody(BodyType type, const shared<Collider>& collider, float mass, float friction) noexcept;
		~RigidBody() noexcept;
		btRigidBody* GetBody() const { return m_Body.get(); }
		void SetAddedToWorld(bool added) { m_AddedToWorld = added; }
		bool IsAddedToWorld() const noexcept { return m_AddedToWorld; }

		float GetMass() const noexcept { return m_Mass; }
		void SetMass(float mass);

		float GetFriction() const noexcept { return m_Friction; }
		void SetFriction(float friction);

		BodyType GetBodyType() const { return m_BodyType; }
		void SetBodyType(BodyType type);

		void SetPosition(const glm::vec3& position);
		glm::vec3 GetPosition() const;
		void SetRotation(const glm::quat& rotation);
		glm::quat GetRotation() const;
		void SetScale(const glm::vec3& scale);
		glm::vec3 GetScale() const;

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
