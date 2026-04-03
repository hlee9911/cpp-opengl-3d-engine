#include "Bullet.h"

void Bullet::Update(float deltaTime)
{
	eng::GameObject::Update(deltaTime);

	m_LifeTime -= deltaTime;
	if (m_LifeTime <= 0.0f)
	{
		MarkForDestroy();
	}
}
