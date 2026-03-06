#pragma once

#include "Core.h"

#include <glm/vec3.hpp>

class btCollisionShape;

namespace eng
{
	class Collider
	{
	public:
		virtual ~Collider() noexcept;
		btCollisionShape* GetShape() const noexcept { return m_Shape; }

	protected:
		btCollisionShape* m_Shape = nullptr;
	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(const glm::vec3& extents) noexcept;
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider(float radius) noexcept;
	};

	class CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(float radius, float height) noexcept;
	};
}
