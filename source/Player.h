#pragma once

#include <eng.h>

class Player : public eng::GameObject
{
	GAMEOBJECT(Player)

public:
	void Init() override;
	void Update(float deltaTime) override;

private:
	eng::AnimationComponent* m_AnimationComponent = nullptr;
};

