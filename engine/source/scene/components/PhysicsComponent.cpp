#include "scene/components/PhysicsComponent.h"
#include "scene/GameObject.h"
#include "Engine.h"

namespace eng
{
	PhysicsComponent::PhysicsComponent(const shared<RigidBody>& body) noexcept
		: m_RigidBody{ body }
	{

	}

	// load the properties from the json formatted file
	void PhysicsComponent::LoadProperties(const nlohmann::json& json)
	{
		// load collider properties
		shared<Collider> collider;

		if (json.contains("collider"))
		{
			const auto& colliderObj = json["collider"];
			std::string type = colliderObj.value("type", "");

			if (type == "box")
			{
				glm::vec3 extents(
					colliderObj.value("x", 1.0f),
					colliderObj.value("y", 1.0f),
					colliderObj.value("z", 1.0f)
				);
				collider = std::make_shared<BoxCollider>(extents);
			}
			else if (type == "sphere")
			{
				float radius = colliderObj.value("r", 1.0f);
				collider = std::make_shared<SphereCollider>(radius);
			}
			else if (type == "capsule")
			{
				float radius = colliderObj.value("r", 1.0f);
				float height = colliderObj.value("h", 1.0f);
				collider = std::make_shared<CapsuleCollider>(radius, height);
			}

			if (!collider) return;

			// load rigidBody properties
			shared<RigidBody> rigidBody;

			if (json.contains("body"))
			{
				const auto& bodyObj = json["body"];

				float mass = bodyObj.value("mass", 0.0f);
				float friction = bodyObj.value("friction", 0.5f);
				std::string typeStr = bodyObj.value("type", "static");

				BodyType type = BodyType::Static;
				if (typeStr == "dynamic")
				{
					type = BodyType::Dynamic;
				}
				else if (typeStr == "kinematic")
				{
					type = BodyType::Kinematic;
				}

				rigidBody = std::make_shared<RigidBody>(type, collider, mass, friction);
			}

			if (rigidBody)
			{
				SetRigidBody(rigidBody);
			}
		}
	}

	void PhysicsComponent::Init()
	{
		if (!m_RigidBody) return;

		// sync the RigidBody's transform with the GameObject's transform
		const auto pos = m_Owner->GetWorldPosition();
		const auto rot = m_Owner->GetWorldRotation();

		m_RigidBody->SetPosition(pos);
		m_RigidBody->SetRotation(rot);

		Engine::GetInstance().GetPhysicsManager().AddRigidBody(m_RigidBody.get());
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		if (!m_RigidBody) return;

		// sync the GameObject's transform with the RigidBody's transform
		if (m_RigidBody->GetBodyType() == BodyType::Dynamic)
		{
			m_Owner->SetWorldPosition(m_RigidBody->GetPosition());
			m_Owner->SetWorldRotation(m_RigidBody->GetRotation());
		}
	}
}
