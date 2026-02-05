#include "scene/components/CameraComponent.h"
#include "scene/GameObject.h"

#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	void CameraComponent::Update(float deltaTime)
	{

	}

	glm::mat4 CameraComponent::GetViewMatrix() const
	{
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::mat4_cast(m_Owner->GetRotation());

		// mat = glm::translate(mat, m_Owner->GetPosition());

		// make it more like fps camera perspective
		mat[3] = glm::vec4(m_Owner->GetPosition(), 1.0f); // aovids translating in the rotated basis

		// we skip scale, since it doesnt make sense for a viewMatrix
		
		if (m_Owner->GetParent())
		{
			mat = m_Owner->GetParent()->GetWorldTransform() * mat;
		}

		return glm::inverse(mat);
		// return glm::inverse(m_Owner->GetWorldTransform());
	}

	glm::mat4 CameraComponent::GetProjectionMatrix(float aspect) const
	{
		return glm::perspective(glm::radians(m_FOV), aspect, m_NearPlane, m_FarPlane);
	}


}
