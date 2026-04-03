#pragma once

#include <vector>
#include <string>
#include <memory>
#include <utility>

#include <nlohmann/json.hpp>

#include "scene/GameObject.h"
#include "Core.h"
#include "Common.h"

namespace eng
{
	class Scene 
	{
	public:
		static void RegisterTypes();
		void Update(float deltaTime);
		void Clear();

		GameObject* CreateGameObject(const std::string& name, GameObject* parent = nullptr);
		GameObject* CreateGameObject(const std::string& type, const std::string& name, GameObject* parent = nullptr);


		/// <summary>
		/// This template function creates a GameObject of type T, sets its name, and assigns it to a parent GameObject if provided.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name=""></typeparam>
		/// <param name="name"></param>
		/// <param name="parent"></param>
		/// <returns></returns>
		template<typename T, typename = typename std::enable_if_t<std::is_base_of_v<GameObject, T>>>
		T* CreateGameObject(const std::string& name, GameObject* parent = nullptr)
		{
			auto gameObject = new T();
			gameObject->SetName(name);
			gameObject->m_Scene = this;
			if (m_IsUpdating)
			{
				m_GameObjectsToAdd.push_back({ gameObject, parent });
			}
			else
			{
				SetParent(gameObject, parent);
			}
			return gameObject;
		}

		bool SetParent(GameObject* obj, GameObject* parent);

		void SetMainCamera(GameObject* camera) noexcept { m_MainCamera = camera; }
		GameObject* GetMainCamera() const noexcept { return m_MainCamera; }

		List<LightData> CollectLights();

		static shared<Scene> Load(const std::string& path);

	private:
		void CollectLightsRecursive(GameObject* obj, List<LightData>& out);

		void LoadObject(const nlohmann::json& jsonObject, GameObject* parent);

	private:
		List<unique<GameObject>> m_GameObjects;
		List<std::pair<GameObject*, GameObject*>> m_GameObjectsToAdd;
		GameObject* m_MainCamera = nullptr;
		bool m_IsUpdating = false;
	};
}
