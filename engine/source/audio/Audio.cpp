#include "audio/Audio.h"
#include "Engine.h"
#include <miniaudio.h>

namespace eng
{
	Audio::~Audio() noexcept
	{
		if (m_Sound)
		{
			ma_sound_uninit(m_Sound.get());
		}
		
		if (m_Decoder)
		{
			ma_decoder_uninit(m_Decoder.get());
		}
	}

	void Audio::SetPosition(const glm::vec3& position)
	{
		if (m_Sound)
		{
			ma_sound_set_position(m_Sound.get(), position.x, position.y, position.z);
		}
	}

	void Audio::Play(bool loop)
	{
		if (m_Sound)
		{
			ma_sound_start(m_Sound.get());
			auto looping = loop ? MA_TRUE : MA_FALSE;
			ma_sound_set_looping(m_Sound.get(), looping);
		}
	}

	void Audio::Stop()
	{
		if (m_Sound)
		{
			ma_sound_stop(m_Sound.get());
			ma_sound_seek_to_pcm_frame(m_Sound.get(), 0);
		}
	}

	bool Audio::IsPlaying() const
	{
		if (m_Sound)
		{
			return ma_sound_is_playing(m_Sound.get());
		}
		return false;
	}

	void Audio::SetVolume(float volume)
	{
		if (m_Sound)
		{
			ma_sound_set_volume(m_Sound.get(), std::clamp(volume, 0.0f, 1.0f));
		}
	}

	float Audio::GetVolume() const
	{
		if (m_Sound)
		{
			return ma_sound_get_volume(m_Sound.get());
		}
		return 0.0f;
	}

	shared<Audio> Audio::Load(const std::string& path)
	{
		// create an audio object and initialize it with the file data
		auto buffer = Engine::GetInstance().GetFileSystem().LoadAssetFile(path);
		auto audioEngine = Engine::GetInstance().GetAudioManager().GetEngine();

		auto audio = std::make_shared<Audio>();
		audio->m_Sound = std::make_unique<ma_sound>();
		audio->m_Buffer = buffer;
		audio->m_Decoder = std::make_unique<ma_decoder>();

		auto result = ma_decoder_init_memory(audio->m_Buffer.data(),
			audio->m_Buffer.size(), nullptr, audio->m_Decoder.get());
		if (result != MA_SUCCESS)
		{
			ERROR("Failed to initialize audio decoder for file: ", path);
			return nullptr;
		}

		result = ma_sound_init_from_data_source(
			audioEngine, 
			audio->m_Decoder.get(),
			0, 
			NULL, 
			audio->m_Sound.get()
		);
		if (result != MA_SUCCESS)
		{
			ERROR("Failed to initialize audio sound for file: ", path);
			return nullptr;
		}

		ma_sound_set_spatialization_enabled(audio->m_Sound.get(), MA_TRUE);
		return audio;
	}

}
