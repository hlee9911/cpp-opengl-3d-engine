#pragma once
#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "scene/Component.h"

#include <glm/mat4x4.hpp>

namespace eng
{
	class CameraComponent : public Component
	{
	public:
		void Update(float deltaTime) override;

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;

	private:

	};
}

#endif // CAMERACOMPONENT_H
