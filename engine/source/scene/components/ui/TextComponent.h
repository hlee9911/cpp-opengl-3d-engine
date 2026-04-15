#pragma once

#include "scene/components/ui/UIElementComponent.h"

#include <string>

namespace eng
{
	class TextComponent : public UIElementComponent
	{
		COMPONENT_WITH_PARENT(TextComponent, UIElementComponent)

	public:
		void Render(CanvasComponent* canvas) override;

		void SetText(const std::string& text) noexcept { m_Text = text; }
		const std::string& GetText() const noexcept { return m_Text; }
		
	private:
		std::string m_Text;
	};
}