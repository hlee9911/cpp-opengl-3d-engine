#pragma once
#ifndef PLAYERCONTROLLERCOMPONENT_H
#define PLAYERCONTROLLERCOMPONENT_H

#include "scene/Component.h"

namespace eng
{
	class PlayerControllerComponent : public Component
	{
		COMPONENT(PlayerControllerComponent)

	public:
		void Update(float deltaTime) override;

	private:
		float m_Sensitivity = 1.5f;
		float m_MoveSpeed = 3.0f;
	};
}

#endif // PLAYERCONTROLLERCOMPONENT_H
