#pragma once

#include "scene/Component.h"

namespace eng
{
	// This component represents the audio listener in the scene
	class AudioListenerComponent : public Component
	{
		COMPONENT(AudioListenerComponent)
	
	public:
		void Update(float deltaTime) override;
	};
}
