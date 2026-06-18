#include "scene/components/PlayerControllerComponent.h"
#include "scene/components/CameraComponent.h"
#include "input/InputManager.h"
#include "Engine.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

#include <iostream>
#include <string>

namespace eng
{
	void PlayerControllerComponent::Init()
	{
		m_KinematicController = std::make_unique<KinematicCharacterController>(1.2f, 0.05f, m_Owner->GetWorldPosition());
	}

	void PlayerControllerComponent::Update(float deltaTime)
	{
		auto& inputManager = Engine::GetInstance().GetInputManager();
		auto& editorManager = Engine::GetInstance().GetEditorManager();
		auto rotation = m_Owner->GetRotation(); // Yaw uses y-axis and Pitch uses the x-axis

		// if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		if (inputManager.IsMousePositionChanged() && !editorManager.GetEditorCursorEnabled())
		{
			const auto& oldPos = inputManager.GetMousePositionOld();
			const auto& currentPos = inputManager.GetMousePositionCurrent();

			float deltaX = currentPos.x - oldPos.x;
			float deltaY = currentPos.y - oldPos.y;

			// rotation around Y axis, when moving deltaX, rotate left and right
			float yDeltaAngle = -deltaX * m_Sensitivity * deltaTime;
			m_yRot += yDeltaAngle;
			glm::quat yRot = glm::angleAxis(glm::radians(m_yRot), glm::vec3(0.0f, 1.0f, 0.0f));
			// rotation.y -= deltaX * m_Sensitivity * deltaTime;

			// rotation around X axis
			float xDeltaAngle = -deltaY * m_Sensitivity * deltaTime;
			m_xRot += xDeltaAngle;
			m_xRot = std::clamp(m_xRot, -80.0f, 80.0f); // clamp the pitch to prevent flipping
			glm::quat xRot = glm::angleAxis(glm::radians(m_xRot), glm::vec3(1.0f, 0.0f, 0.0f));
			// glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f); // gives the camera's current local right direction
			// rotation.x -= deltaY * m_Sensitivity * deltaTime;

			// glm::quat deltaRot = yRot * xRot;
			// rotation = glm::normalize(deltaRot * rotation); // with quaternion, most transform are just quaternion multiplications
			rotation = glm::normalize(yRot * xRot); // with quaternion, most transform are just quaternion multiplications

			m_Owner->SetRotation(rotation);
		}

		//glm::mat4 rotMat(1.0f);
		//rotMat = glm::rotate(rotMat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
		//rotMat = glm::rotate(rotMat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
		//rotMat = glm::rotate(rotMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis

		// better approach: using only yaw for the movement
		// fixes the jump height inconsistency issue 
		float yaw = glm::radians(m_yRot);

		glm::vec3 front(
			-sinf(yaw),
			0.0f,
			-cosf(yaw));

		glm::vec3 right(
			cosf(yaw),
			0.0f,
			-sinf(yaw));

		//// calculate forward and right vector
		//glm::vec3 front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		//glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);

		//// remove any vertical component caused by camera pitch
		//front.y = 0.0f;
		//right.y = 0.0f;

		//// renormalize after removing y
		//front = glm::normalize(front);
		//right = glm::normalize(right);
	
		// auto position = m_Owner->GetPosition();

		glm::vec3 movement(0.0f);

		if (!editorManager.GetEditorCursorEnabled())
		{
			// Right/Left movement
			if (inputManager.IsKeyPressed(GLFW_KEY_A))
			{
				// position -= right * m_MoveSpeed * deltaTime;
				movement -= right;
			}
			else if (inputManager.IsKeyPressed(GLFW_KEY_D))
			{
				// position += right * m_MoveSpeed * deltaTime;
				movement += right;
			}

			// Forward/Backward movement
			if (inputManager.IsKeyPressed(GLFW_KEY_W))
			{
				// position += front * m_MoveSpeed * deltaTime;
				movement += front;
			}
			else if (inputManager.IsKeyPressed(GLFW_KEY_S))
			{
				// position -= front * m_MoveSpeed * deltaTime;
				movement -= front;
			}
			// m_Owner->SetPosition(position);

			if (inputManager.WasKeyPressed(GLFW_KEY_SPACE))
			{
				m_KinematicController->Jump(glm::vec3(0.0f, m_JumpForce, 0.0f));
			}

			// return the player back to the starting position in case something terrible happens to the player
			if (inputManager.WasKeyPressed(GLFW_KEY_R))
			{
				Logger::Log("Setting player's position back to starting position");
				m_KinematicController->SetPosition(m_Owner->GetStartingPosition());
			}

		}

		// normalize the movement vector to prevent faster diagonal movement
		if (glm::dot(movement, movement) > 0)
		{
			movement = glm::normalize(movement);
		}

		//Logger::Log(
		//	"Movement Y: " +
		//	std::to_string(movement.y));

		// account for sprinting
		if (inputManager.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			m_KinematicController->Walk(movement * m_SprintSpeed * deltaTime);
		}
		else
		{
			m_KinematicController->Walk(movement * m_WalkSpeed * deltaTime);
		}

		// sync the scene objects position and rotation with the kinematic controller
		// m_Owner->SetPosition(m_KinematicController->GetPosition());

		glm::vec3 capsuleCenter = m_KinematicController->GetPosition();
		m_Owner->SetPosition(capsuleCenter);

		// camera position offset to match with the eye line
		auto camera = m_Owner->GetComponent<CameraComponent>();
		if (camera)
		{
			glm::vec3 eyeOffset(0.0f, 0.9f, 0.0f);
			camera->GetOwner()->SetWorldPosition(capsuleCenter + eyeOffset);
		}
	}

	bool PlayerControllerComponent::IsOnGround() const
	{
		if (m_KinematicController)
		{
			return m_KinematicController->IsOnGround();
		}
		return false;
	}
}
