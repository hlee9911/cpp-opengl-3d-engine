#include "scene/components/AudioComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void AudioComponent::LoadPropertiesFromJson(const nlohmann::json& json)
	{
		if (json.contains("audio"))
		{
			auto& clipsObject = json["audio"];
			for (auto& clip : clipsObject)
			{
				std::string name = clip.value("name", "noname");
				std::string filePath = clip.value("path", "");
				auto audio = Audio::LoadFromJson(filePath);
				if (audio)
				{
					float volume = clip.value("volume", 1.0f);
					audio->SetVolume(volume);
					RegisterAudio(name, audio);
				}
			}
		}
	}

	void AudioComponent::LoadPropertiesFromLua(const sol::table& table)
	{
		if (LuaLoaderUtil::LuaHasKey(table, "audio"))
		{
			sol::object clipsObjRaw = table.get<sol::object>("audio");
			if (LuaLoaderUtil::LuaIsTable(clipsObjRaw))
			{
				sol::table clipsObject = clipsObjRaw.as<sol::table>();
				for (auto& kv : clipsObject)
				{
					if (!LuaLoaderUtil::LuaIsTable(kv.second)) continue;
					sol::table clip = kv.second.as<sol::table>();

					std::string name = LuaLoaderUtil::LuaValueOrStr(clip, "name", "noname");
					std::string filePath = LuaLoaderUtil::LuaValueOrStr(clip, "path", "");
					auto audio = Audio::LoadFromJson(filePath);
					if (audio)
					{
						float volume = LuaLoaderUtil::LuaValueOr<float>(clip, "volume", 1.0f);
						audio->SetVolume(volume);
						RegisterAudio(name, audio);
					}
				}
			}
		}
	}

	void AudioComponent::Update(float deltaTime)
	{
		auto pos = m_Owner->GetWorldPosition();
		for (auto& clip : m_AudioClips)
		{
			if (clip.second->IsPlaying())
			{
				clip.second->SetPosition(pos);
			}
		}
	}

	void AudioComponent::RegisterAudio(const std::string& name, shared<Audio>& clip)
	{
		m_AudioClips[name] = clip;
	}

	void AudioComponent::Play(const std::string& name, bool loop)
	{
		auto it = m_AudioClips.find(name);
		if (it != m_AudioClips.end())
		{
			if (it->second)
			{
				it->second->Play(loop);
			}
		}
	}

	void AudioComponent::Stop(const std::string& name)
	{
		auto it = m_AudioClips.find(name);
		if (it != m_AudioClips.end())
		{
			if (it->second)
			{
				it->second->Stop();
			}
		}
	}

	bool AudioComponent::IsPlaying(const std::string& name) const
	{
		auto it = m_AudioClips.find(name);
		if (it != m_AudioClips.end())
		{
			if (it->second)
			{
				return it->second->IsPlaying();
			}
		}
		return false;
	}

}
