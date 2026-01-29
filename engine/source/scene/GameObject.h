#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>

namespace eng
{
	class GameObject
	{
	public:
		virtual ~GameObject() noexcept = default;
		virtual void Update(float deltaTime);
		
		const std::string& GetName() const noexcept;
		void SetName(const std::string& name) noexcept;

		GameObject* GetParent() noexcept;
		bool IsAlive() const noexcept;

		void MarkForDestroy();

	protected:
		GameObject() noexcept = default;

	private:
		std::string m_Name;
		GameObject* m_Parent = nullptr;
		std::vector<std::unique_ptr<GameObject>> m_Children;
		bool m_IsAlive = true;

		friend class Scene;
	};
}

#endif // GAMEOBJECT_H
