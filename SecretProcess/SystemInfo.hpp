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
	std::wstring get_firmware_type();
	std::wstring get_keyboard_layout();
	bool running_on_vm();
	void save_system_info();
}