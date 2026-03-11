#include "scene/Component.h"

namespace eng
{
	size_t Component::nextId = 1;

	void Component::LoadProperties(const nlohmann::json& json)
	{

	}

	void Component::Init()
	{
		
	}

	ComponentFactory& ComponentFactory::GetInstance()
	{
		static ComponentFactory instance;
		return instance;
	}
}
