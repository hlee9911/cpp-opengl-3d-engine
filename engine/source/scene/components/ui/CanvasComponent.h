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
		virtual void LoadPropertiesFromJson(const nlohmann::json& json) override;
		virtual void LoadPropertiesFromLua(const sol::table& table) override;
		virtual void Update(float deltaTime) override;
		virtual void Init() override;
		void Render(UIElementComponent* element);
		void BeginRendering();
		void Flush();
		void CollectUI(UIElementComponent* element, List<UIElementComponent*>& out);

		void DrawRect(
			const glm::vec2& lowerLeftPos, const glm::vec2& upperRightPos,
			const glm::vec2& lowerLeftUV, const glm::vec2& upperRightUV,
			Texture* texture, const glm::vec4& color
		);
		void DrawRect(
			const glm::vec2& lowerLeftPos, const glm::vec2& upperRightPos,
			const glm::vec4& color
		);

		void SetActive(bool active) noexcept { m_Active = active; }
		bool IsActive() const noexcept { return m_Active; }

	private:
		void UpdateBatches(Texture* texture);

	private:
		List<UIBatch> m_Batches;
		List<float> m_Veriticies;
		List<uint32_t> m_Indicies;
		shared<Mesh> m_Mesh;
		bool m_Active = true;
	};
}
