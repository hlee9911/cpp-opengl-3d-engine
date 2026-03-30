#include "audio/AudioManager.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

namespace eng
{
	AudioManager::AudioManager() noexcept
	{
		m_AudioEngine = std::make_unique<ma_engine>();

	}

	AudioManager::~AudioManager() noexcept
	{
		if (m_AudioEngine)
		{
			ma_engine_uninit(m_AudioEngine.get());
		}
	}

	bool AudioManager::Init()
	{
		auto result = ma_engine_init(nullptr, m_AudioEngine.get());
		return result == MA_SUCCESS;
	}

	ma_engine* AudioManager::GetEngine()
	{
		return m_AudioEngine.get();
	}

	void AudioManager::SetListenerPosition(const glm::vec3& pos)
	{
		if (m_AudioEngine)
		{
			ma_engine_listener_set_position(m_AudioEngine.get(), 0, pos.x, pos.y, pos.z);
		}
	}
}
