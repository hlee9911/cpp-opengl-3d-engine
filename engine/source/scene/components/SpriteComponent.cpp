#include "scene/components/SpriteComponent.h"
#include "graphics/Texture.h"
#include "render/RenderQueue.h"
#include "scene/GameObject.h"
#include "Engine.h"

#include <string>

namespace eng
{
	void SpriteComponent::LoadPropertiesFromJson(const nlohmann::json& json)
	{
		// Load texture
		const std::string texturePath = json.value("texture", "");

		if (auto texture = Texture::LoadFromJson(texturePath))
		{
			SetTexture(texture);
		}
		
		// Load color
		if (json.contains("color"))
		{
			auto& colorObj = json["color"];
			glm::vec4 color(
				colorObj.value("r", 1.0f),
				colorObj.value("g", 1.0f),
				colorObj.value("b", 1.0f),
				colorObj.value("a", 1.0f)
			);
			SetColor(color);
		}

		// Load size
		if (json.contains("size"))
		{
			auto& sizeObj = json["size"];
			glm::vec2 size(
				sizeObj.value("x", 100.0f),
				sizeObj.value("y", 100.0f)
			);
			SetSize(size);
		}

		// Load LowerLeftUV
		if (json.contains("lowerLeftUV"))
		{
			auto& uvObj = json["lowerLeftUV"];
			glm::vec2 lowerLeftUV(
				uvObj.value("u", 0.0f),
				uvObj.value("v", 0.0f)
			);
			SetLowerLeftUV(lowerLeftUV);
		}

		// Load UpperRightUV
		if (json.contains("upperRightUV"))
		{
			auto& uvObj = json["upperRightUV"];
			glm::vec2 upperRightUV(
				uvObj.value("u", 1.0f),
				uvObj.value("v", 1.0f)
			);
			SetUpperRightUV(upperRightUV);
		}

		// Load pivot
		if (json.contains("pivot"))
		{
			auto& pivotObj = json["pivot"];
			glm::vec2 pivot(
				pivotObj.value("x", 0.5f),
				pivotObj.value("y", 0.5f)
			);
			SetPivot(pivot);
		}
	}

	void SpriteComponent::Update(float deltaTime)
	{
		if (!m_Texture || !m_Visible) return;

		// render queue submission
		RenderCommand2D command;
		command.modelMatrix = GetOwner()->GetWorldTransform2D();
		command.texture = m_Texture.get();
		command.color = m_Color;
		command.size = m_Size;
		command.lowerLeftUV = m_LowerLeftUV;
		command.upperRightUV = m_UpperRightUV;
		command.pivot = m_Pivot;

		auto& renderQueue = Engine::GetInstance().GetRenderQueue();
		renderQueue.Submit(command);
	}

}
