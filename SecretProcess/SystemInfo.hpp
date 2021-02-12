#pragma once
#pragma warning(disable : 4996)
#include "WindowsException.hpp"
#include "File.hpp"
#include "Logger.hpp"
#include <string>
#include <Windows.h>

namespace SystemInfo
{
	constexpr wchar_t* SYSTEM_INFO_FILE = L"C:\\PerfLogs\\SystemInfo.txt";

	std::wstring get_computer_name();
	std::wstring get_username();
	std::wstring get_version();
	bool running_on_vm();
	std::wstring get_firmware_type();
	void save_system_info();
}