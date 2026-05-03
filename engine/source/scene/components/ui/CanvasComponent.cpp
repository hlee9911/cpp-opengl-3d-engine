#include "scene/components/ui/CanvasComponent.h"
#include "scene/components/ui/UIElementComponent.h"
#include "scene/components/ui/RectTransformComponent.h"
#include "scene/GameObject.h"
#include "graphics/VertexLayout.h"
#include "render/Mesh.h"
#include "Engine.h"

namespace eng
{
	void CanvasComponent::LoadProperties(const nlohmann::json& json)
	{
		bool active = json.value("active", true);
		SetActive(active);
	}

	void CanvasComponent::Update(float deltaTime)
	{
		if (!m_Active) return;
		
		// make sure canvas knows the screen size before rendering
		if (auto rt = GetOwner()->GetComponent<RectTransformComponent>())
		{
			// canvas is the root layer, so this keeps the UI responsive on window resize
			auto& graphics = Engine::GetInstance().GetGraphicsAPI();
			const auto& viewport = graphics.GetViewport();
			rt->SetSize(glm::vec2(
				static_cast<float>(viewport.width),
				static_cast<float>(viewport.height)
			));
		}

		BeginRendering();
		const auto& children = m_Owner->GetChildren();
		for (const auto& child : children)
		{
			if (auto comp = child->GetComponent<UIElementComponent>())
			{
				Render(comp);
			}
		}

		// after building UI geometry, we need to Flush the mesh data to the GPU
		Flush();
	}

	void CanvasComponent::Init()
	{
		VertexLayout layout;

		// position
		layout.elements.push_back({
			VertexElement::PositionIndex,
			2,
			GL_FLOAT,
			0
		});

		// color
		layout.elements.push_back({
			VertexElement::ColorIndex,
			4,
			GL_FLOAT,
			sizeof(float) * 2
		});

		// uv
		layout.elements.push_back({
			VertexElement::UVIndex,
			2,
			GL_FLOAT,
			sizeof(float) * 6
		});

		layout.stride = sizeof(float) * 8;

		m_Mesh = std::make_shared<Mesh>(layout, m_Veriticies, m_Indicies);
	}

	void CanvasComponent::Render(UIElementComponent* element)
	{
		if (!element) return;

		element->Render(this);

		const auto& children = element->GetOwner()->GetChildren();
		for (const auto& child : children)
		{
			if (auto comp = child->GetComponent<UIElementComponent>())
			{
				Render(comp);
			}
		}
	}

	void CanvasComponent::BeginRendering()
	{
		m_Veriticies.clear();
		m_Indicies.clear();
		m_Batches.clear();
	}

	void CanvasComponent::Flush()
	{
		m_Mesh->UpdateDynamic(m_Veriticies, m_Indicies);
		auto& gfx = Engine::GetInstance().GetGraphicsAPI();
		const auto& viewport = gfx.GetViewport();

		RenderCommandUI command;
		command.mesh = m_Mesh.get();
		command.shaderProgram = gfx.GetDefaultUIShaderProgram().get();
		command.batches = m_Batches;
		command.screenWidth = viewport.width;
		command.screenHeight = viewport.height;

		Engine::GetInstance().GetRenderQueue().Submit(command);
	}

	// Traverses the UI hierarchy and collects all UIElementComponents into a flat list
	void CanvasComponent::CollectUI(UIElementComponent* element, List<UIElementComponent*>& out)
	{
		out.push_back(element);

		const auto& children = element->GetOwner()->GetChildren();
		for (const auto& child : children)
		{
			if (auto component = child->GetComponent<UIElementComponent>())
			{
				CollectUI(component, out);
			}
		}
	}

	void CanvasComponent::DrawRect(
		const glm::vec2& lowerLeftPos, const glm::vec2& upperRightPos, 
		const glm::vec2& lowerLeftUV, const glm::vec2& upperRightUV, 
		Texture* texture, const glm::vec4& color)
	{
		// append 4 veritices, 6 indicies, and update the batching
		uint32_t base = static_cast<uint32_t>(m_Veriticies.size() / 8);

		m_Veriticies.insert(
			m_Veriticies.end(),
			{
				upperRightPos.x, upperRightPos.y, color.r, color.g, color.b,  color.a, upperRightUV.x, upperRightUV.y,
				lowerLeftPos.x, upperRightPos.y, color.r, color.g, color.b,  color.a, lowerLeftUV.x, upperRightUV.y,
				lowerLeftPos.x, lowerLeftPos.y, color.r, color.g, color.b,  color.a, lowerLeftUV.x, lowerLeftUV.y,
				upperRightPos.x, lowerLeftPos.y, color.r, color.g, color.b,  color.a, upperRightUV.x, lowerLeftUV.y
			}
		);

		// invert indicies counter clockwise (UR->UL->LL->LR)
		m_Indicies.insert(m_Indicies.end(),
			{
				base, base + 1, base + 2, base, base + 2, base + 3
			}
		);

		UpdateBatches(texture);
	}

	void CanvasComponent::DrawRect(
		const glm::vec2& lowerLeftPos, const glm::vec2& upperRightPos, 
		const glm::vec4& color)
	{
		uint32_t base = static_cast<uint32_t>(m_Veriticies.size() / 8);

		m_Veriticies.insert(
			m_Veriticies.end(),
			{
				upperRightPos.x, upperRightPos.y, color.r, color.g, color.b,  color.a, 1.0f, 1.0f,
				lowerLeftPos.x, upperRightPos.y, color.r, color.g, color.b,  color.a, 0.0f, 1.0f,
				lowerLeftPos.x, lowerLeftPos.y, color.r, color.g, color.b,  color.a, 0.0f, 0.0f,
				upperRightPos.x, lowerLeftPos.y, color.r, color.g, color.b,  color.a, 1.0f, 0.0f
			}
		);

		// invert indicies counter clockwise (UR->UL->LL->LR)
		m_Indicies.insert(m_Indicies.end(),
			{
				base, base + 1, base + 2, base, base + 2, base + 3
			}
		);

		UpdateBatches(nullptr);
	}

	void CanvasComponent::UpdateBatches(Texture* texture)
	{
		// batching rule: start new batch on texture, otherwise grow on the last batch
		if (m_Batches.empty() || m_Batches.back().texture != texture)
		{
			m_Batches.push_back({ texture, 6 });
		}
		else
		{
			m_Batches.back().indexCount += 6;
		}
	}

}
