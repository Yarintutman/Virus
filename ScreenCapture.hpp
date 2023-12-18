#pragma once

#include <windows.h>
#include <string>
#include <expected>
#include <thread>

const std::string FOLDER_NAME = "\\Screenshots";
const std::string SCREENSHOT_FOLDER = "\\Pictures\\Screenshots";

/// <summary>
/// Takes Screenshots of the screen
/// </summary>
class ScreenCapture
{
public:
	int SetDirectory(const char*);
	std::thread StartScreenCapture(uint32_t);
	void SetDefaultDirectory();
	void TakeScreenShot();
	void StopScreenCapture();
	ScreenCapture();
	ScreenCapture(ScreenCapture&);
	ScreenCapture(const char*);
private:
	std::string directory;
	bool captureState;
	void StartScreenCaptureThread(uint32_t seconds);
	std::string  GetUserDirectory();
	int CreateScreenshotFolder();
	void CreateScreenShot();
	std::string CreateFileName();
};
