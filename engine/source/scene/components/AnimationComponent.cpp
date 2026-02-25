#include "scene/components/AnimationComponent.h"
#include "scene/GameObject.h"

namespace eng
{
	void AnimationComponent::Update(float deltaTime)
	{
		if (!m_Clip) return;
		if (!m_IsPlaying) return;

		m_CurrentTime += deltaTime;

		if (m_CurrentTime > m_Clip->duration)
		{
			// Handle looping or stop
			if (m_Looping)
			{
				m_CurrentTime = std::fmod(m_CurrentTime, m_Clip->duration);
			}
			else
			{
				m_CurrentTime = 0.0f;
				m_IsPlaying = false;
				return;
			}
		}

		for (auto& binding : m_Bindings)
		{
			auto& obj = binding.first;
			auto& trackIndicies = binding.second->trackIndices;
			for (auto i : trackIndicies)
			{
				auto& track = m_Clip->tracks[i];
				if (!track.positions.empty())
				{
					auto pos = Interpolate(track.positions, m_CurrentTime);
					obj->SetPosition(pos);
				}
				if (!track.rotations.empty())
				{
					auto rot = Interpolate(track.rotations, m_CurrentTime);
					obj->SetRotation(rot);
				}
				if (!track.scales.empty())
				{
					auto scale = Interpolate(track.scales, m_CurrentTime);
					obj->SetScale(scale);
				}
			}
		}
	}

	/// <summary>
	/// Sets the current animation clip to play. This will reset the current time to 0 and start playing the animation.
	/// </summary>
	/// <param name="clip"></param>
	void AnimationComponent::SetClip(AnimationClip* clip)
	{
		m_Clip = clip;
		BuildBindings();
	}

	/// <summary>
	/// Registers an animation clip with a given name. This allows you to play the clip later by name using the Play method.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="clip"></param>
	void AnimationComponent::RegisterClip(const std::string& name, const shared<AnimationClip>& clip)
	{
		m_Clips[name] = clip;
	}

	/// <summary>
	/// Plays an animation clip by name. If the clip is already playing, it will reset the current time to 0 and start playing again. 
	/// If the clip is not found, it sets new clip from the registered clips and starts playing.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="looping"></param>
	void AnimationComponent::Play(const std::string& name, bool looping)
	{
		if (m_Clip && m_Clip->name == name)
		{
			m_CurrentTime = 0.0f;
			m_IsPlaying = true;
			m_Looping = looping;
		}
		else
		{
			auto it = m_Clips.find(name);
			if (it != m_Clips.end())
			{
				SetClip(it->second.get());
				m_CurrentTime = 0.0f;
				m_IsPlaying = true;
				m_Looping = looping;
			}
		}
	}

	/// <summary>
	/// Builds the bindings between the animation tracks and the game objects in the scene. 
	/// This will iterate through all the tracks in the current clip and find the corresponding game object in the scene by name.
	/// </summary>
	void AnimationComponent::BuildBindings()
	{
		m_Bindings.clear();
		if (!m_Clip) return;

		for (size_t i = 0; i < m_Clip->tracks.size(); ++i)
		{
			auto& track = m_Clip->tracks[i];
			auto targetObject = m_Owner->FindChildByName(track.targetName);
			if (targetObject)
			{
				auto it = m_Bindings.find(targetObject);
				// if binding exists, push the index into trackIndices
				if (it != m_Bindings.end())
				{
					it->second->trackIndices.push_back(i);
				}
				else
				{
					// otherwise, create a new binding and add it to the dictionary
					auto binding = std::make_unique<ObjectBinding>();
					binding->object = targetObject;
					binding->trackIndices.push_back(i);
					m_Bindings.emplace(targetObject, std::move(binding));
				}
			}
		}
	}

	/// <summary>
	/// Interpolates the value of a keyframe at a given time. 
	/// This will find the two keyframes that surround the current time and interpolate between them using linear interpolation for vec3 and spherical linear interpolation for quaternions.
	/// </summary>
	/// <param name="keyframes"></param>
	/// <param name="time"></param>
	/// <returns></returns>
	glm::vec3 AnimationComponent::Interpolate(const List<KeyFrameVec3>& keyframes, float time)
	{
		if (keyframes.empty()) return glm::vec3(0.0f);
		if (keyframes.size() == 1) return keyframes[0].value;
		if (time <= keyframes.front().time) return keyframes.front().value;
		if (time >= keyframes.back().time) return keyframes.back().value;

		size_t i0 = 0;
		size_t i1 = 0;

		// Find the two keyframes that surround the current time
		for (size_t i = 1; i < keyframes.size(); i++)
		{
			if (time <= keyframes[i].time)
			{
				i1 = i;
				break;
			}
		}

		i0 = i1 > 0 ? i1 - 1 : 0;

		// Interpolate between keyframes[i0] and keyframes[i1]
		if (time >= keyframes[i0].time && time <= keyframes[i1].time)
		{
			float deltaTime = keyframes[i1].time - keyframes[i0].time;
			float k = (time - keyframes[i0].time) / deltaTime;

			return glm::mix(keyframes[i0].value, keyframes[i1].value, k);
		}

		return keyframes.back().value;
	}

	/// <summary>
	/// Interpolates the value of a keyframe at a given time.
	/// This will find the two keyframes that surround the current time and interpolate between them using linear interpolation for vec3 and spherical linear interpolation for quaternions.
	/// </summary>
	/// <param name="keyframes"></param>
	/// <param name="time"></param>
	/// <returns></returns>
	glm::quat AnimationComponent::Interpolate(const List<KeyFrameQuat>& keyframes, float time)
	{
		if (keyframes.empty()) return glm::vec3(0.0f);
		if (keyframes.size() == 1) return keyframes[0].value;
		if (time <= keyframes.front().time) return keyframes.front().value;
		if (time >= keyframes.back().time) return keyframes.back().value;

		size_t i0 = 0;
		size_t i1 = 0;

		// Find the two keyframes that surround the current time
		for (size_t i = 1; i < keyframes.size(); i++)
		{
			// find the first key where key.time is greater than the current time
			if (time <= keyframes[i].time)
			{
				i1 = i;
				break;
			}
		}

		i0 = i1 > 0 ? i1 - 1 : 0;

		// Interpolate between keyframes[i0] and keyframes[i1]
		if (time >= keyframes[i0].time && time <= keyframes[i1].time)
		{
			float deltaTime = keyframes[i1].time - keyframes[i0].time;
			float k = (time - keyframes[i0].time) / deltaTime;

			return glm::slerp(keyframes[i0].value, keyframes[i1].value, k);
		}

		return keyframes.back().value;
	}


}
