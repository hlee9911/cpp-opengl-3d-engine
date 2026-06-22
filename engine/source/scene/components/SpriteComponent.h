#pragma once

#include "scene/Component.h"
#include "Core.h"

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

namespace eng
{
	class Texture;

	/// <summary>
	/// SpriteComponent is responsible for rendering a 2D sprite
	/// </summary>
	class SpriteComponent : public Component
	{
		COMPONENT(SpriteComponent)

	public:
		virtual void LoadPropertiesFromJson(const nlohmann::json& json) override;
		virtual void LoadPropertiesFromLua(const sol::table& table) override;
		virtual void Update(float deltaTime) override;

		void SetTexture(const shared<Texture>& texture) noexcept { m_Texture = texture; }
		const shared<Texture>& GetTexture() const noexcept { return m_Texture; }

		void SetColor(const glm::vec4& color) noexcept { m_Color = color; }
		const glm::vec4& GetColor() const noexcept { return m_Color; }

		void SetSize(const glm::vec2& size) noexcept { m_Size = size; }
		const glm::vec2& GetSize() const noexcept { return m_Size; }

		void SetLowerLeftUV(const glm::vec2& uv) noexcept { m_LowerLeftUV = uv; }
		const glm::vec2& GetLowerLeftUV() const noexcept { return m_LowerLeftUV; }
		void SetUpperRightUV(const glm::vec2& uv) noexcept { m_UpperRightUV = uv; }
		const glm::vec2& GetUpperRightUV() const noexcept { return m_UpperRightUV; }
		void SetUV(const glm::vec2& lowerLeftUV, const glm::vec2& upperRightUV) noexcept
		{
			m_LowerLeftUV = lowerLeftUV;
			m_UpperRightUV = upperRightUV;
		}

		void SetPivot(const glm::vec2& pivot) noexcept { m_Pivot = pivot; }
		const glm::vec2& GetPivot() const noexcept { return m_Pivot; }

		void SetVisible(bool visible) noexcept { m_Visible = visible; }
		bool IsVisible() const noexcept { return m_Visible; }

	private:
		shared<Texture> m_Texture;
		glm::vec4 m_Color = glm::vec4(1.0f);
		glm::vec2 m_Size = glm::vec2(100.0f);
		glm::vec2 m_LowerLeftUV = glm::vec2(0.0f);
		glm::vec2 m_UpperRightUV = glm::vec2(1.0f);
		glm::vec2 m_Pivot = glm::vec2(0.5f);
		bool m_Visible = true;
	};
}