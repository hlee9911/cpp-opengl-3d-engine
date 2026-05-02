#include "render/RenderQueue.h"
#include "render/Mesh.h"
#include "render/Material.h"
#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"

#include <glm/gtc/matrix_transform.hpp>

namespace eng
{
	void RenderQueue::Init()
	{
		m_Mesh2D = Mesh::CreatePlane();
	}

	void RenderQueue::Submit(const RenderCommand& command)
	{
		m_Commands.push_back(command);
	}

	void RenderQueue::Submit(const RenderCommand2D& command)
	{
		m_Commands2D.push_back(command);
	}

	void RenderQueue::Submit(const RenderCommandUI& command)
	{
		m_CommandsUI.push_back(command);
	}

	void RenderQueue::Draw(GraphicsAPI& graphicsAPI, const CameraData& cameraData, const List<LightData>& lights)
	{
		// Render 3D objects
		for (auto& command : m_Commands)
		{
			graphicsAPI.BindMaterial(command.material);
			auto shaderProgram = command.material->GetShaderProgram();
			shaderProgram->SetUniform("uModel", command.modelMatrix);
			shaderProgram->SetUniform("uView", cameraData.viewMatrix);
			shaderProgram->SetUniform("uProjection", cameraData.projectionMatrix);
			shaderProgram->SetUniform("uCameraPos", cameraData.position);

			if (!lights.empty())
			{
				auto& light = lights[0];
				shaderProgram->SetUniform("uLight.color", light.color);
				shaderProgram->SetUniform("uLight.direction", glm::normalize(-light.position));
			}

			graphicsAPI.BindMesh(command.mesh);
			graphicsAPI.DrawMesh(command.mesh);
			graphicsAPI.UnbindMesh(command.mesh);
		}

		m_Commands.clear();

		// Render 2D objects
		graphicsAPI.SetDepthTestEnabled(false); // disable depth testing for 2D rendering
		graphicsAPI.SetBlendMode(BlendMode::Alpha); // enable alpha blending for 2D rendering
		const auto shaderProgram2D = graphicsAPI.GetDefault2DShaderProgram();
		shaderProgram2D->Bind();

		// bind the mesh first
		m_Mesh2D->Bind();
		for (auto& command : m_Commands2D)
		{
			// render
			shaderProgram2D->SetUniform("uModel", command.modelMatrix);
			shaderProgram2D->SetUniform("uView", cameraData.viewMatrix);
			// 2D uses an orthographic projection not a perspective projection
			shaderProgram2D->SetUniform("uProjection", cameraData.orthoMatrix);
			shaderProgram2D->SetUniform("uSize", command.size.x, command.size.y);
			shaderProgram2D->SetUniform("uPivot", command.pivot.x, command.pivot.y);
			shaderProgram2D->SetUniform("uUVMin", command.lowerLeftUV.x, command.lowerLeftUV.y);
			shaderProgram2D->SetUniform("uUVMax", command.upperRightUV.x, command.upperRightUV.y);
			shaderProgram2D->SetUniform("uColor", command.color);
			shaderProgram2D->SetTexture("uTex", command.texture);
			m_Mesh2D->Draw();
		}
		// unbind the mesh
		m_Mesh2D->Unbind();
		graphicsAPI.SetBlendMode(BlendMode::Disabled); // disable blending after 2D rendering
		// this ensures to isolates the 2D rendering state changes from the 3D rendering
		graphicsAPI.SetDepthTestEnabled(true); // re-enable depth testing for 3D rendering
		m_Commands2D.clear();
		
		// Render UI Objects
		graphicsAPI.SetDepthTestEnabled(false); // disable depth testing for UI rendering
		graphicsAPI.SetBlendMode(BlendMode::Alpha); // enable alpha blending for UI rendering
		// we render UI objects in batches, so we loop through the commands and render each batch one by one
		for (auto& command : m_CommandsUI)
		{
			glm::mat4 ortho = glm::ortho(
				0.0f, static_cast<float>(command.screenWidth),
				0.0f, static_cast<float>(command.screenHeight)
			);
			command.shaderProgram->Bind();
			command.shaderProgram->SetUniform("uProjection", ortho);

			command.mesh->Bind();

			uint32_t indexBase = 0;
			// each batch corresponds to a draw call, so we loop through the batches and draw them one by one
			for (auto& batch : command.batches)
			{
				if (batch.texture)
				{
					command.shaderProgram->SetUniform("uUseTexture", 1);
					command.shaderProgram->SetTexture("uTex", batch.texture);
				}
				else
				{
					command.shaderProgram->SetUniform("uUseTexture", 0);
				}
				command.mesh->DrawIndexedRange(indexBase, batch.indexCount);
				indexBase += batch.indexCount;
			}
			command.mesh->Unbind();
		}
		graphicsAPI.SetBlendMode(BlendMode::Disabled); // disable blending after UI rendering
		graphicsAPI.SetDepthTestEnabled(true); // re-enable depth testing for 3D rendering
		m_CommandsUI.clear();
	}
}
