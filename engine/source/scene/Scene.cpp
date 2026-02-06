#include "scene/Scene.h"

namespace eng
{
	void Scene::Update(float deltaTime)
	{
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end();)
		{
			if ((*it)->IsAlive())
			{
				(*it)->Update(deltaTime);
				++it;
			}
			else
			{
				it = m_GameObjects.erase(it);
			}
		}
	}

	void Scene::Clear()
	{
		m_GameObjects.clear();
	}

	GameObject* Scene::CreateGameObject(const std::string& name, GameObject* parent)
	{
		auto gameObject = new GameObject();
		gameObject->SetName(name);
		SetParent(gameObject, parent);
		return gameObject;
	}

	/// <summary>
	/// This function sets the parent of a GameObject to another GameObject.
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="parent"></param>
	/// <returns></returns>
	bool Scene::SetParent(GameObject* obj, GameObject* parent)
	{
		bool result = false;
		auto currentParent = obj->GetParent();

		if (!parent)
		{
			if (currentParent)
			{
				auto it = std::find_if(
					currentParent->m_Children.begin(),
					currentParent->m_Children.end(),
					[obj](const unique<GameObject>& el)
					{
						return el.get() == obj;
					}
				);

				if (it != currentParent->m_Children.end())
				{
					m_GameObjects.push_back(std::move(*it));
					obj->m_Parent = nullptr;
					currentParent->m_Children.erase(it);
					result = true;
				}
			}
			// No parent currently. This can be in 2 cases
			// 1. The object is in the scene root
			// 2. The object has been just created
			else
			{
				// search for the object in the scene root
				auto it = std::find_if(
					m_GameObjects.begin(),
					m_GameObjects.end(),
					[obj](const unique<GameObject>& el)
					{
						return el.get() == obj;
					}
				);

				// object is not found in the scene root, so it must be newly created
				if (it == m_GameObjects.end())
				{
					unique<GameObject> objHolder(obj);
					m_GameObjects.push_back(std::move(objHolder));
					result = true;
				}
			}
		}
		// we are trying to add it as a child of another object
		else
		{
			if (currentParent)
			{
				auto it = std::find_if(
					currentParent->m_Children.begin(),
					currentParent->m_Children.end(),
					[obj](const unique<GameObject>& el)
					{
						return el.get() == obj;
					}
				);

				if (it != currentParent->m_Children.end())
				{
					// never assign a child to one of its own children
					bool found = false;
					auto currentElement = parent;
					while (currentElement)
					{
						if (currentElement == obj)
						{
							found = true;
							break;
						}
						currentElement = currentElement->GetParent();
					}

					// if everything is ok, perform the re-parenting
					if (!found)
					{
						parent->m_Children.push_back(std::move(*it));
						obj->m_Parent = parent;
						currentParent->m_Children.erase(it);
						result = true;
					}
				}
			}
			// No parent currently. This can be in 2 cases
			// 1. The object is in the scene root
			// 2. The object has been just created
			else
			{
				// search for the object in the scene root
				auto it = std::find_if(
					m_GameObjects.begin(),
					m_GameObjects.end(),
					[obj](const unique<GameObject>& el)
					{
						return el.get() == obj;
					}
				);

				// The object has been just created
				if (it == m_GameObjects.end())
				{
					unique<GameObject> objHolder(obj);
					parent->m_Children.push_back(std::move(objHolder));
					obj->m_Parent = parent;
					result = true;
				}
				// The object is in the scene root
				else
				{
					// check for cyclic parenting
					bool found = false;
					auto currentElement = parent;
					while (currentElement)
					{
						if (currentElement == obj)
						{
							found = true;
							break;
						}
						currentElement = currentElement->GetParent();
					}

					// if everything is ok, perform the parenting
					if (!found)
					{
						parent->m_Children.push_back(std::move(*it));
						obj->m_Parent = parent;
						m_GameObjects.erase(it);
						result = true;
					}
				}
			}
		}

		return result;
	}
}
