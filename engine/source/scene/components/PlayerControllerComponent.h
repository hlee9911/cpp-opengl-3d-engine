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

		float GetMouseSensitivity() const noexcept { return m_Sensitivity; }
		void SetMouseSensitivity(float sensitivity) noexcept { m_Sensitivity = sensitivity; }

		float GetWalkSpeed() const noexcept { return m_WalkSpeed; }
		void SetWalkSpeed(float walkSpeed) noexcept { m_WalkSpeed = walkSpeed; }

		float GetSprintSpeed() const noexcept { return m_SprintSpeed; }
		void SetSprintSpeed(float sprintSpeed) noexcept { m_SprintSpeed = sprintSpeed; }

		float GetJumpForce() const noexcept { return m_JumpForce; }
		void SetJumpForce(float jumpForce) noexcept { m_JumpForce = jumpForce; }

	private:
		float m_Sensitivity = 27.5f;
		float m_WalkSpeed = 10.0f;
		float m_SprintSpeed = 17.5f;
		float m_JumpForce = 5.0f;
		float m_xRot = 0.0f; // pitch
		float m_yRot = 0.0f; // yaw
		unique<KinematicCharacterController> m_KinematicController;
	};
}
