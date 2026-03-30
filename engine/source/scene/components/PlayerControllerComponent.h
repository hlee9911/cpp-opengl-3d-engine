#pragma once

#include "scene/Component.h"
#include "physics/KinematicCharacterController.h"
#include "Core.h"

namespace eng
{
	class PlayerControllerComponent : public Component
	{
		COMPONENT(PlayerControllerComponent)

	public:
		void Init() override;
		void Update(float deltaTime) override;

		bool IsOnGround() const;

	private:
		float m_Sensitivity = 27.5f;
		float m_MoveSpeed = 12.5f;
		float m_xRot = 0.0f; // pitch
		float m_yRot = 0.0f; // yaw
		unique<KinematicCharacterController> m_KinematicController;
	};
}
