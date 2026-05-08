#include "Logger.h"

#include <iostream>
#include <ctime>
#include <chrono>

namespace eng
{
	std::vector<LogEntry> Logger::messagesStack;

	/// <summary>
	/// Returns the current date and time as a string
	/// </summary>
	/// <returns></returns>
	std::string Logger::CurrentDateTimeToString()
	{
		std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string output(30, '\0');
		struct tm timeInfo;
		localtime_s(&timeInfo, &now);
		std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", &timeInfo);
		return output;
	}

	/// <summary>
	/// Prints the message to the console and adds it to the messagesStack
	/// The message is in the format: LOG: [currentDateTime]: message
	/// </summary>
	/// <param name="message"></param>
	void Logger::Log(const std::string& message)
	{
		LogEntry logEntry;
		logEntry.type = LogType::LOG_INFO;
		logEntry.message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;
		std::cout << "\x1B[32m" << logEntry.message << "\033[0m" << "\n"; // change the color to green (fgcode 32)

		messagesStack.emplace_back(logEntry);
	}

	/// <summary>
	/// Prints the message to the console and adds it to the messagesStack
	/// The message is in the format: WAR: [currentDateTime]: message
	/// </summary>
	/// <param name="message"></param>
	void Logger::Warning(const std::string& message)
	{
		LogEntry logEntry;
		logEntry.type = LogType::LOG_WARNING;
		logEntry.message = "WAR: [" + CurrentDateTimeToString() + "]: " + message;
		std::cout << "\x1B[33m" << logEntry.message << "\033[0m" << "\n"; // change the color to yellow (fgcode 33)

		messagesStack.emplace_back(logEntry);
	}

	/// <summary>
	/// Prints the message to the console and adds it to the messagesStack
	/// The message is in the format: ERR: [currentDateTime]: message
	/// </summary>
	/// <param name="message"></param>
	void Logger::Error(const std::string& message)
	{
		LogEntry logEntry;
		logEntry.type = LogType::LOG_ERROR;
		logEntry.message = "ERR: [" + CurrentDateTimeToString() + "]: " + message;
		std::cerr << "\x1B[91m" << logEntry.message << "\033[0m" << "\n"; // change the color to red (fgcode 91)

		messagesStack.emplace_back(logEntry);
	}
}
