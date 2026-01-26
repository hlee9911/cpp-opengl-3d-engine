#pragma once
#ifndef GAME_H
#define GAME_H

#include <eng.h>

class Game : public eng::Application
{
public:
	bool Init() override;
	void Update(float deltaTime) override;
	void Destroy() override;

private:
	eng::Material m_Material;
};

#endif // GAME_H
