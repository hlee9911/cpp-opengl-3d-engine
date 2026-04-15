#include "scene/components/ui/CanvasComponent.h"
#include "scene/components/ui/UIElementComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void CanvasComponent::Update(float deltaTime)
	{
		const auto& children = m_Owner->GetChildren();
		for (const auto& child : children)
		{
			if (auto comp = child->GetComponent<UIElementComponent>())
			{
				Render(comp);
			}
		}
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
}
