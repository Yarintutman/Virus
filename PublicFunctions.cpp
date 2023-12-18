#include "PublicFunctions.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/types.h>

namespace fs = std::filesystem;

std::wstring PublicFunctions::StringToWString(const std::string& str)
{
	std::wstring wstr;
	size_t size;
	wstr.resize(str.length());
	mbstowcs_s(&size, &wstr[0], wstr.size() + 1, str.c_str(), str.size());
	return wstr;
}

std::string PublicFunctions::WStringToString(const std::wstring& wstr)
{
	std::string str;
	size_t size;
	str.resize(wstr.length());
	wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
	return str;
}

std::string PublicFunctions::GetLastCreatedFile(const std::string folder)
{
	std::string lastcreatedfile = "none";
	for (const auto& file : fs::directory_iterator(folder))
	{
		fs::file_time_type modificationDate = fs::last_write_time(file.path());
		if ((lastcreatedfile == "none" || modificationDate > fs::last_write_time(lastcreatedfile)))
		{
			lastcreatedfile = file.path().string();
		}
	}
	return lastcreatedfile;
}
