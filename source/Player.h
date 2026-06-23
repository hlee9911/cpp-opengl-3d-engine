#pragma once

#include <eng.h>

class Player : public eng::GameObject
{
	GAMEOBJECT(Player)

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;

private:
	eng::AnimationComponent* m_AnimationComponent = nullptr;
	eng::AudioComponent* m_AudioComponent = nullptr;
	eng::PlayerControllerComponent* m_PlayerControllerComponent = nullptr;
};

