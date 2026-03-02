#pragma once

#include <glm/mat4x4.hpp>

#include <vector>

#include "Common.h"
#include "Core.h"

namespace eng
{
	class Mesh;
	class Material;
	class GraphicsAPI;

	struct RenderCommand
	{
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		glm::mat4 modelMatrix = glm::mat4(0.0f);
	};

	class RenderQueue
	{
	public:
		void Submit(const RenderCommand& command);
		void Draw(GraphicsAPI& graphicsAPI, const CameraData& cameraData, const List<LightData>& lights);

	private:
		List<RenderCommand> m_Commands;
	};
}
