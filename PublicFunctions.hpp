#pragma once

#include <string>

/// <summary>
/// this class contains usefull functions
/// </summary>
class PublicFunctions
{
public:
	static std::wstring StringToWString(const std::string& str);
	static std::string WStringToString(const std::wstring& wstr);
	static std::string GetLastCreatedFile(const std::string);
};