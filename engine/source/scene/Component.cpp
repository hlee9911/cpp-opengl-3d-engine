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

	void Component::Update(float deltaTime)
	{

	}

	ComponentFactory& ComponentFactory::GetInstance()
	{
		static ComponentFactory instance;
		return instance;
	}

	bool ComponentFactory::HasParent(size_t objectType, size_t parentType)
	{
		auto record = m_ParentMap.find(objectType);
		if (record == m_ParentMap.end())
		{
			return false;
		}

		auto& parents = record->second;
		if (std::find(parents.begin(), parents.end(), parentType) != parents.end())
		{
			return true;
		}

		for (auto p : parents)
		{
			if (HasParent(p, parentType))
			{
				return true;
			}
		}

		return false;
	}
}
