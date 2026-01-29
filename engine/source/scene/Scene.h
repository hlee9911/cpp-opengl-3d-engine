#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include <memory>

#include "scene/GameObject.h"

namespace eng
{
	class Scene 
	{
	public:
		void Update(float deltaTime);
		void Clear();

		GameObject* CreateGameObject(const std::string& name, GameObject* parent = nullptr);

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
			SetParent(gameObject, parent);
			return gameObject;
		}

		bool SetParent(GameObject* obj, GameObject* parent);

	private:
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;
	};
}

#endif // SCENE_H
