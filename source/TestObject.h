#pragma once
#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <eng.h>

class TestObject : public eng::GameObject
{
public:
	TestObject() noexcept;

	void Update(float deltaTime) override;

private:
	eng::Material m_Material;
	std::shared_ptr<eng::Mesh> m_Mesh; // we can share the mesh between multiple objects
	//float m_OffsetX = 0.0f;
	//float m_OffsetY = 0.0f;
};

#endif // TESTOBJECT_H
