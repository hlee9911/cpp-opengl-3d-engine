#pragma once

#include <string>
#include <vector>

namespace eng
{
	enum LogType
	{
		LOG_INFO = 0,
		LOG_WARNING,
		LOG_ERROR,
	};

	struct LogEntry
	{
		LogType type = LogType::LOG_INFO;
		std::string message = "";
	};

	class Logger
	{
	public:
		static std::string CurrentDateTimeToString();

		static void Log(const std::string& message);
		static void Warning(const std::string& message);
		static void Error(const std::string& message);

		// one big container that contains all the messages
		static std::vector<LogEntry> messagesStack;
	};
}
