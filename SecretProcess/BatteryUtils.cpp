#pragma once
#include "pch.h"
#include "BatteryUtils.hpp"

std::wstring BatteryUtils::ac_status()
{
	SYSTEM_POWER_STATUS power_status = BatteryUtils::get_power_status();

	switch (power_status.ACLineStatus)
	{
	case 0:
		return L"Not plugged to AC";
	case 1:
		return L"Plugged to AC";
	case 255:
		return L"AC status is unkown";
	default:
		return L"Unknown";
	}
}

std::wstring BatteryUtils::get_battery_status()
{
	SYSTEM_POWER_STATUS power_status = BatteryUtils::get_power_status();

	switch (power_status.BatteryFlag)
	{
	case 0:
		return L"MEDIUM ( 66% > battery < 33% )";
	case 1:
		return L"HIGH ( > 66% )";
	case 2:
		return L"LOW ( < 33% )";
	case 4:
		return L"CRITICAL ( < 5% )";
	case 8:
		return L"CHARGING";
	case 128:
		return L"NO BATTERY";
	case 255:
		return L"Unkown battery status";
	default:
		return L"Uknown";
	}
}

std::wstring BatteryUtils::get_battery_percent()
{
	SYSTEM_POWER_STATUS power_status = BatteryUtils::get_power_status();

	return L"Battery percentage: " + std::to_wstring(power_status.BatteryLifePercent) + L'%';
}

std::wstring BatteryUtils::get_battery_saver()
{
	SYSTEM_POWER_STATUS power_status = BatteryUtils::get_power_status();

	switch (power_status.Reserved1)
	{
	case 0:
		return L"Battery saver is OFF";
	case 1:
		return L"Battery saver is ON";
	default:
		return L"Unknown";
	}
}

SYSTEM_POWER_STATUS BatteryUtils::get_power_status()
{
	SYSTEM_POWER_STATUS power_status;

	if (!GetSystemPowerStatus(&power_status))
	{
		throw WindowsException();
	}

	return power_status;
}

void BatteryUtils::save_battery_info()
{
	Logger::Instance().info(L"Saving battery info");

	File battery_info{BATTERY_INFO_FILE};

	battery_info.write(L"<<<<<<<<<<<<<<<<<<< DITTO BATTERY INFO >>>>>>>>>>>>>>>>>>>>>>\n");
	battery_info.write(L"AC Status: " + BatteryUtils::ac_status() + L"\n");
	battery_info.write(L"Battery Status: " + BatteryUtils::get_battery_status() + L"\n");
	battery_info.write(BatteryUtils::get_battery_percent() + L"\n");
	battery_info.write(L"Battery Saver: " + BatteryUtils::get_battery_saver() + L"\n");
}