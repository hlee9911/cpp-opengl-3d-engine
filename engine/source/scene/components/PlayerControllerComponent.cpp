#include "scene/components/PlayerControllerComponent.h"
#include "input/InputManager.h"
#include "Engine.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace eng
{
	void PlayerControllerComponent::Update(float deltaTime)
	{
		auto& inputManager = Engine::GetInstance().GetInputManager();
		auto rotation = m_Owner->GetRotation(); // Yaw uses y-axis and Pitch uses the x-axis

		if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			const auto& oldPos = inputManager.GetMousePositionOld();
			const auto& currentPos = inputManager.GetMousePositionCurrent();

			float deltaX = currentPos.x - oldPos.x;
			float deltaY = currentPos.y - oldPos.y;

			// rotation around Y axis, when moving deltaX, rotate left and right
			float yAngle = -deltaX * m_Sensitivity * deltaTime;
			glm::quat yRot = glm::angleAxis(yAngle, glm::vec3(0.0f, 1.0f, 0.0f));
			// rotation.y -= deltaX * m_Sensitivity * deltaTime;

			// rotation around X axis
			float xAngle = -deltaY * m_Sensitivity * deltaTime;
			glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f); // gives teh camera's current local right direction
			glm::quat xRot = glm::angleAxis(xAngle, right);
			// rotation.x -= deltaY * m_Sensitivity * deltaTime;

			glm::quat deltaRot = yRot * xRot;
			rotation = glm::normalize(deltaRot * rotation); // with quaternion, most transform are just quaternion multiplications

			m_Owner->SetRotation(rotation);
		}

		//glm::mat4 rotMat(1.0f);
		//rotMat = glm::rotate(rotMat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
		//rotMat = glm::rotate(rotMat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
		//rotMat = glm::rotate(rotMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis

		// calculate forward and right vector
		glm::vec3 front = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	
		auto position = m_Owner->GetPosition();

		// Right/Left movement
		if (inputManager.IsKeyPressed(GLFW_KEY_A))
		{
			position -= right * m_MoveSpeed * deltaTime;
		}
		else if (inputManager.IsKeyPressed(GLFW_KEY_D))
		{
			position += right * m_MoveSpeed * deltaTime;
		}

		// Forward/Backward movement
		if (inputManager.IsKeyPressed(GLFW_KEY_W))
		{
			position += front * m_MoveSpeed * deltaTime;
		}
		else if (inputManager.IsKeyPressed(GLFW_KEY_S))
		{
			position -= front * m_MoveSpeed * deltaTime;
		}
		m_Owner->SetPosition(position);
	}
}
