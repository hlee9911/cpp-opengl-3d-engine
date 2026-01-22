#include "Application.h"

namespace eng
{
	void Application::SetNeedsToBeClosed(bool value)
	{
		m_NeedsToBeClosed = value;
	}

	bool Application::NeedsToBeClosed() const
	{
		return m_NeedsToBeClosed;
	}
}
