#include "physics/CollisionObject.h"

namespace eng
{
	/// <summary>
	/// Adds a contact listener to this collision object. The listener will be notified when a collision occurs with this object
	/// </summary>
	/// <param name="listener"></param>
	void CollisionObject::AddContactListener(IContactListener* listener)
	{
		m_ContactListeners.push_back(listener);
	}
	
	/// <summary>
	/// Removes a contact listener from this collision object. This should be called when the listener is destroyed to avoid dangling pointers
	/// </summary>
	/// <param name="listener"></param>
	void CollisionObject::RemoveContactListener(IContactListener* listener)
	{
		auto it = std::find(m_ContactListeners.begin(), m_ContactListeners.end(), listener);
		if (it != m_ContactListeners.end())
		{
			m_ContactListeners.erase(it);
		}
	}

	/// <summary>
	/// Dispatches a contact event to all registered listeners. This should be called by the physics engine when a collision occurs
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="pos"></param>
	/// <param name="norm"></param>
	void CollisionObject::DispatchContactEvent(
		CollisionObject* obj, 
		const glm::vec3& pos, 
		const glm::vec3& norm)
	{
		for (auto listener : m_ContactListeners)
		{
			if (listener)
			{
				listener->OnContact(obj, pos, norm);
			}
		}
	}
}
