#pragma once

#include <eng.h>

class TestObject : public eng::GameObject
{
public:
	TestObject() noexcept;

	void Update(float deltaTime) override;

private:
	
};
