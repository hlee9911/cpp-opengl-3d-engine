#pragma once
#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <glm/mat4x4.hpp>

#include <vector>

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
		void Draw(GraphicsAPI& graphicsAPI);

	private:
		std::vector<RenderCommand> m_Commands;
	};
}

#endif // RENDERQUEUE_H
