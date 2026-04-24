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
	class Texture;
	class ShaderProgram;

	struct RenderCommand
	{
		Mesh* mesh = nullptr;
		Material* material = nullptr;
		glm::mat4 modelMatrix = glm::mat4(0.0f);
	};

	struct RenderCommand2D
	{
		glm::mat4 modelMatrix = glm::mat4(0.0f);
		Texture* texture = nullptr;
		glm::vec4 color = glm::vec4(1.0f);
		glm::vec2 size = glm::vec2(100.0f);
		glm::vec2 lowerLeftUV = glm::vec2(0.0f);
		glm::vec2 upperRightUV = glm::vec2(1.0f);
		glm::vec2 pivot = glm::vec2(0.5f);
	};

	struct RenderCommandUI
	{
		Mesh* mesh = nullptr;
		ShaderProgram* shaderProgram = nullptr;
		size_t screenWidth = 0;
		size_t screenHeight = 0;
		List<UIBatch> batches;
	};

	class RenderQueue
	{
	public:
		void Init();
		void Submit(const RenderCommand& command);
		void Submit(const RenderCommand2D& command);
		void Submit(const RenderCommandUI& command);
		void Draw(GraphicsAPI& graphicsAPI, const CameraData& cameraData, const List<LightData>& lights);

	private:
		List<RenderCommand> m_Commands;
		List<RenderCommand2D> m_Commands2D;
		List<RenderCommandUI> m_CommandsUI;
		shared<Mesh> m_Mesh2D;
	};
}
