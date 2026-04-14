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
		// bind the mesh first
		m_Mesh2D->Bind();
		for (auto& command : m_Commands2D)
		{
			// render
			m_Mesh2D->Draw();
		}
		// unbind the mesh
		m_Mesh2D->Unbind();
	}
}
