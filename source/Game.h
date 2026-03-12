#pragma once

#include <eng.h>

#include "Core.h"

class Game : public eng::Application
{
public:
	bool Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

private:
	eng::Scene* m_Scene = nullptr;
};
