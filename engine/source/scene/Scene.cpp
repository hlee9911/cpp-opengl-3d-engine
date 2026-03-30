#include "scene/Scene.h"
#include "scene/components/AnimationComponent.h"
#include "scene/components/CameraComponent.h"
#include "scene/components/LightComponent.h"
#include "scene/components/MeshComponent.h"
#include "scene/components/PhysicsComponent.h"
#include "scene/components/PlayerControllerComponent.h"
#include "scene/components/AudioComponent.h"
#include "scene/components/AudioListenerComponent.h"
#include "Engine.h"

namespace eng
{
	void Scene::RegisterTypes()
	{
		AnimationComponent::Register();
		CameraComponent::Register();
		LightComponent::Register();
		MeshComponent::Register();
		PhysicsComponent::Register();
		PlayerControllerComponent::Register();
		AudioComponent::Register();
		AudioListenerComponent::Register();
	}

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
		gameObject->m_Scene = this;
		SetParent(gameObject, parent);
		return gameObject;
	}

	// this function will be used to create a object while loading the scene
	GameObject* Scene::CreateGameObject(const std::string& type, const std::string& name, GameObject* parent)
	{
		auto gameObject = GameObjectFactory::GetInstance().CreateGameObject(type);
		if (gameObject)
		{
			gameObject->SetName(name);
			gameObject->m_Scene = this;
			SetParent(gameObject, parent);
		}
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

	List<LightData> Scene::CollectLights()
	{
		List<LightData> lights;
		for (auto& obj : m_GameObjects)
		{
			CollectLightsRecursive(obj.get(), lights);
		}
		return lights;
	}

	shared<Scene> Scene::Load(const std::string& path)
	{
		const std::string contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);
		if (contents.empty()) return nullptr;

		auto json = nlohmann::json::parse(contents);
		if (json.empty()) return nullptr;

		auto result = std::make_shared<Scene>();

		const std::string sceneName = json.value("name", "noname");

		if (json.contains("objects") && json["objects"].is_array())
		{
			const auto& objects = json["objects"];

			for (const auto& obj : objects)
			{
				result->LoadObject(obj, nullptr);
			}
		}

		if (json.contains("camera"))
		{
			std::string cameraObjName = json.value("camera", "");
			for (const auto& child : result->m_GameObjects)
			{
				if (auto object = child->FindChildByName(cameraObjName))
				{
					result->SetMainCamera(object);
					break;
				}
			}
		}

		return result;
	}

	/// <summary>
	/// Collects light data from the scene recursively, starting from the given GameObject. If the GameObject has a LightComponent, its data is added to the output list. The function then continues to check all child GameObjects.
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="out"></param>
	void Scene::CollectLightsRecursive(GameObject* obj, List<LightData>& out)
	{
		if (auto light = obj->GetComponent<LightComponent>())
		{
			LightData data;
			data.color = light->GetColor();
			data.position = obj->GetWorldPosition();
			out.push_back(data);
		}

		for (auto& child : obj->m_Children)
		{
			CollectLightsRecursive(child.get(), out);
		}
	}

	void Scene::LoadObject(const nlohmann::json& jsonObject, GameObject* parent)
	{
		const std::string name = jsonObject.value("name", "Object");

		GameObject* gameObject = nullptr;

		if (jsonObject.contains("type"))
		{
			const std::string type = jsonObject.value("type", "");
			if (type == "gltf")
			{
				// gltf loading
				std::string path = jsonObject.value("path", "");
				gameObject = GameObject::LoadGLTF(path, this);
				if (gameObject)
				{
					gameObject->SetParent(parent);
					gameObject->SetName(name);
				}
			}
			else
			{
				gameObject = CreateGameObject(type, name, parent);
			}
		}
		else
		{
			// create object
			gameObject = CreateGameObject(name, parent);
		}

		if (!gameObject) return;

		// load transform
		if (jsonObject.contains("position"))
		{
			auto posObj = jsonObject["position"];
			glm::vec3 pos;
			pos.x = posObj.value("x", 0.0f);
			pos.y = posObj.value("y", 0.0f);
			pos.z = posObj.value("z", 0.0f);
			gameObject->SetPosition(pos);
		}

		if (jsonObject.contains("rotation"))
		{
			auto rotObj = jsonObject["rotation"];
			glm::quat rot;
			rot.x = rotObj.value("x", 0.0f);
			rot.y = rotObj.value("y", 0.0f);
			rot.z = rotObj.value("z", 0.0f);
			rot.w = rotObj.value("w", 1.0f);
			gameObject->SetRotation(rot);
		}

		if (jsonObject.contains("scale"))
		{
			auto scaleObj = jsonObject["scale"];
			glm::vec3 scale;
			scale.x = scaleObj.value("x", 1.0f);
			scale.y = scaleObj.value("y", 1.0f);
			scale.z = scaleObj.value("z", 1.0f);
			gameObject->SetScale(scale);
		}

		// load properties
		gameObject->LoadProperties(jsonObject);

		// load components
		if (jsonObject.contains("components") && jsonObject["components"].is_array())
		{
			const auto& components = jsonObject["components"];
			for (const auto& comp : components)
			{
				const std::string type = comp.value("type", "");
				Component* component = ComponentFactory::GetInstance().CreateComponent(type);
				if (component)
				{
					component->LoadProperties(comp);
					gameObject->AddComponenet(component);
				}
			}
		}

		// load children recursively
		if (jsonObject.contains("children") && jsonObject["children"].is_array())
		{
			const auto& children = jsonObject["children"];
			for (const auto& child : children)
			{
				LoadObject(child, gameObject);
			}
		}

		// for post-load setup
		gameObject->Init();
	}
}
