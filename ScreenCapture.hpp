#pragma once

#include <windows.h>
#include <string>
#include <expected>

const std::string FOLDER_NAME = "\\Screenshots";
const std::string SCREENSHOT_FOLDER = "\\Pictures\\Screenshots";

/// <summary>
/// Takes Screenshots of the screen
/// </summary>
class ScreenCapture
{
public:
	int SetDirectory(const char*);
	int StartScreenCapture(uint32_t);
	void SetDefaultDirectory();
	int TakeScreenShot();
	ScreenCapture();
	ScreenCapture(ScreenCapture&);
	ScreenCapture(const char*);
private:
	std::string directory;
	bool captureState;
	std::string  GetUserDirectory();
	int CreateScreenshotFolder();
	void CreateScreenShot();
	std::string CreateFileName();
};
