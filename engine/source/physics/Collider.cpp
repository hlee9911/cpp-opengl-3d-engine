#include "physics/Collider.h"

#include <btBulletCollisionCommon.h>

namespace eng
{
	Collider::~Collider() noexcept
	{
		if (m_Shape)
		{
			delete m_Shape;
			m_Shape = nullptr;
		}
	}
	
	BoxCollider::BoxCollider(const glm::vec3& extents) noexcept
	{
		glm::vec3 halfExtents = extents * 0.5f;
		m_Shape = new btBoxShape(btVector3(halfExtents.x, halfExtents.y, halfExtents.z));
	}

	SphereCollider::SphereCollider(float radius) noexcept
	{
		m_Shape = new btSphereShape(radius);
	}

	CapsuleCollider::CapsuleCollider(float radius, float height) noexcept
	{
		m_Shape = new btCapsuleShape(btScalar(radius), btScalar(height));
	}

}
