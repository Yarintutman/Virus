#include "KeyLogger.hpp"
#include "ScreenCapture.hpp"
#include <windows.h>
#include <WinUser.h>
#include <thread>
#include <expected>

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	//KeyLogger* k = new KeyLogger("C:\\Users\\yarin\\Test");
	//std::thread thread_keyLog = k->StartKeyLogger();
	ScreenCapture* s = new ScreenCapture("C:\\Users\\yarin\\Test");
	std::thread thread_captureScreen = s->StartScreenCapture(3);
	std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000));
	s->StopScreenCapture();
	//k->StopLogging();
	//thread_keyLog.join();
	thread_captureScreen.join();
	delete s;
	//delete k;
	return 0;
}
