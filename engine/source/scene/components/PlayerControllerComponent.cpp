#include "scene/components/PlayerControllerComponent.h"
#include "input/InputManager.h"
#include "Engine.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace eng
{
	void PlayerControllerComponent::Init()
	{
		m_KinematicController = std::make_unique<KinematicCharacterController>(0.4f, 1.2f, m_Owner->GetWorldPosition());
	}

	void PlayerControllerComponent::Update(float deltaTime)
	{
		auto& inputManager = Engine::GetInstance().GetInputManager();
		auto rotation = m_Owner->GetRotation(); // Yaw uses y-axis and Pitch uses the x-axis

		// if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		if (inputManager.IsMousePositionChanged())
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
			m_xRot = std::clamp(m_xRot, -89.0f, 89.0f); // clamp the pitch to prevent flipping
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

		// calculate forward and right vector
		glm::vec3 front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	
		// auto position = m_Owner->GetPosition();

		glm::vec3 movement(0.0f);

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

		if (inputManager.IsKeyPressed(GLFW_KEY_SPACE))
		{
			m_KinematicController->Jump(glm::vec3(0.0f, 5.0f, 0.0f));
		}
		
		// normalize the movement vector to prevent faster diagonal movement
		if (glm::dot(movement, movement) > 0)
		{
			movement = glm::normalize(movement);
		}
		m_KinematicController->Walk(movement * m_MoveSpeed * deltaTime);

		// sync the scene objects position and rotation with the kinematic controller
		m_Owner->SetPosition(m_KinematicController->GetPosition());

	}
}
