#pragma once

#include <eng.h>

class TestObject : public eng::GameObject
{
public:
	TestObject() noexcept;

	virtual void Update(float deltaTime) override;

private:
	
};
