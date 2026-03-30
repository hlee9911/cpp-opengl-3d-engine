#pragma once

#include "Common.h"
#include "Core.h"

struct ma_engine;

namespace eng
{
	class AudioManager
	{
	public:
		AudioManager() noexcept;
		~AudioManager() noexcept;

		bool Init();
		ma_engine* GetEngine();

		void SetListenerPosition(const glm::vec3& pos);

	private:
		unique<ma_engine> m_AudioEngine;
	};
}
