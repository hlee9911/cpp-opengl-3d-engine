#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace eng
{
	struct CameraData
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};

	struct LightData
	{
		glm::vec3 color;
		glm::vec3 position;
	};
}

#endif // COMMON_H
