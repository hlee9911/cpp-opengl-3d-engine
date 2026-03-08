#pragma once

#include <eng.h>

class Player : public eng::GameObject
{
public:
	void Init();
	void Update(float deltaTime) override;

private:
	eng::AnimationComponent* m_AnimationComponent = nullptr;
};

