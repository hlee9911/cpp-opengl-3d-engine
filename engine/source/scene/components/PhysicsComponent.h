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

		virtual void LoadPropertiesFromJson(const nlohmann::json& json) override;
		virtual void LoadPropertiesFromLua(const sol::table& table) override;
		virtual void Init() override;
		virtual void Update(float deltaTime) override;

		virtual void OnEnable() override;
		virtual void OnDisable() override;

		void SetRigidBody(const shared<RigidBody>& body) { m_RigidBody = body; }
		const shared<RigidBody>& GetRigidBody() const { return m_RigidBody; }

	private:
		shared<RigidBody> m_RigidBody;
	};
}