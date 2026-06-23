#pragma once

#include <eng.h>

class JumpPlatform : public eng::GameObject, public eng::IContactListener
{
	GAMEOBJECT(JumpPlatform)

public:
	virtual void Init() override;
	virtual void OnContact(
		eng::CollisionObject* obj,
		const glm::vec3& pos,
		const glm::vec3& norm) override;

private:
	float m_JumpForce = 17.5f;

};
