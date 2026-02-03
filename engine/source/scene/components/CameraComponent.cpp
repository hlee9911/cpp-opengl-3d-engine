#include "scene/components/CameraComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void CameraComponent::Update(float deltaTime)
	{

	}

	glm::mat4 CameraComponent::GetViewMatrix() const
	{
		return glm::inverse(m_Owner->GetWorldTransform());
	}

	glm::mat4 CameraComponent::GetProjectionMatrix() const
	{
		// TODO: Will modify this later on
		return glm::mat4(1.0f);
	}


}
