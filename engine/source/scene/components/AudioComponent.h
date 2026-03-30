#pragma once

#include "Core.h"
#include "scene/Component.h"
#include "audio/Audio.h"

#include <string>

namespace eng
{
	/// <summary>
	/// A component that manages audio clips and their playback for a GameObject. 
	/// </summary>
	class AudioComponent : public Component
	{
		COMPONENT(AudioComponent)

	public:
		void LoadProperties(const nlohmann::json& json) override;
		void Update(float deltaTime) override;

		void RegisterAudio(const std::string& name, shared<Audio>& clip);
		void Play(const std::string& name, bool loop = false);
		void Stop(const std::string& name);
		bool IsPlaying(const std::string& name) const;

	private:
		Dictionary<std::string, shared<Audio>> m_AudioClips;
	};
}