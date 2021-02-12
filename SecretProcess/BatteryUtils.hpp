#pragma once
#include "WindowsException.hpp"
#include "File.hpp"
#include "Logger.hpp"
#include <string>
#include <iostream>
#include <Windows.h>

namespace BatteryUtils
{
	constexpr wchar_t* BATTERY_INFO_FILE = L"C:\\PerfLogs\\BatteryInfo.txt";

	SYSTEM_POWER_STATUS get_power_status();
	std::wstring ac_status();
	std::wstring get_battery_status();
	std::wstring get_battery_percent();
	std::wstring get_battery_saver();
	void save_battery_info();
}