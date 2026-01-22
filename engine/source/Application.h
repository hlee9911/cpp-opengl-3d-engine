#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

namespace eng
{
	class Application
	{
	public:
		virtual bool Init() = 0;
		// deltaTime in seconds
		virtual void Update(float deltaTime) = 0;
		virtual void Destroy() = 0;

		void SetNeedsToBeClosed(bool value);
		bool NeedsToBeClosed() const;

	private:
		bool m_NeedsToBeClosed = false;
	};
}

#endif // APPLICATION_H
