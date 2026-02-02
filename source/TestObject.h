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
	
};

#endif // TESTOBJECT_H
