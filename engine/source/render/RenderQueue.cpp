#include "render/RenderQueue.h"
#include "render/Mesh.h"
#include "render/Material.h"
#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"

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
	}
}
