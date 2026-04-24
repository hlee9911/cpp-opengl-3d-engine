#pragma once

#include "Common.h"
#include "Core.h"
#include "scene/Component.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace eng
{
	class UIElementComponent;
	class Texture;
	class Mesh;
	
	class CanvasComponent : public Component
	{
		COMPONENT(CanvasComponent)

	public:
		void Update(float deltaTime) override;
		void Init() override;
		void Render(UIElementComponent* element);
		void BeginRendering();
		void Flush();

		void DrawRect(
			const glm::vec2& lowerLeftPos, const glm::vec2& upperRightPos,
			const glm::vec2& lowerLeftUV, const glm::vec2& upperRightUV,
			Texture* texture, const glm::vec4& color
		);
		void DrawRect(
			const glm::vec2& lowerLeftPos, const glm::vec2& upperRightPos,
			const glm::vec4& color
		);

	private:
		void UpdateBatches(Texture* texture);

	private:
		List<UIBatch> m_Batches;
		List<float> m_Veriticies;
		List<uint32_t> m_Indicies;
		shared<Mesh> m_Mesh;
	};
}
