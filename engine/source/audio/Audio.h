#pragma once

#include "Common.h"
#include "Core.h"

#include <string>

struct ma_sound;
struct ma_decoder;

namespace eng
{
	class Audio
	{
	public:
		~Audio() noexcept;
		
		void SetPosition(const glm::vec3& position);
		void Play(bool loop = false);
		void Stop();
		bool IsPlaying() const;
		void SetVolume(float volume);
		float GetVolume() const;

		static shared<Audio> Load(const std::string& path);

	private:
		unique<ma_sound> m_Sound;
		unique<ma_decoder> m_Decoder;
		List<char> m_Buffer;
	};
}