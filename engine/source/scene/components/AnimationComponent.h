#pragma once

#include "scene/Component.h"
#include "Core.h"

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>

namespace eng
{
	// class GameObject;
	
	struct KeyFrameVec3
	{
		float time = 0.0f;
		glm::vec3 value = glm::vec3(0.0f);
	};

	struct KeyFrameQuat
	{
		float time = 0.0f;
		glm::quat value = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	};

	struct TransformTrack
	{
		std::string targetName;
		List<KeyFrameVec3> positions;
		List<KeyFrameQuat> rotations;
		List<KeyFrameVec3> scales;
	};

	struct AnimationClip
	{
		std::string name;
		float duration = 0.0f;
		bool looping = true;
		List<TransformTrack> tracks;
	};

	struct ObjectBinding
	{
		GameObject* object = nullptr;
		List<size_t> trackIndices;
	};

	class AnimationComponent : public Component
	{
		COMPONENT(AnimationComponent)
	
	public:
		void Update(float deltaTime) override;

		void SetClip(AnimationClip* clip);
		void RegisterClip(const std::string& name, const shared<AnimationClip>& clip);
		void Play(const std::string& name, bool looping = true);

		bool IsPlaying() const noexcept { return m_IsPlaying; }

	private:
		void BuildBindings();

		glm::vec3 Interpolate(const List<KeyFrameVec3>& keyframes, float time);
		glm::quat Interpolate(const List<KeyFrameQuat>& keyframes, float time);

	private:
		AnimationClip* m_Clip = nullptr;
		float m_CurrentTime = 0.0f;
		bool m_Looping = true;
		bool m_IsPlaying = false;

		Dictionary<std::string, shared<AnimationClip>> m_Clips;
		Dictionary<GameObject*, unique<ObjectBinding>> m_Bindings;
	};
}
