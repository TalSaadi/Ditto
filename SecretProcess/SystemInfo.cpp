#include "pch.h"
#include "SystemInfo.hpp"

std::wstring SystemInfo::get_computer_name()
{
	unsigned long buffer_size = MAX_COMPUTERNAME_LENGTH + 1;
	wchar_t* buffer = new wchar_t[buffer_size];

	if (buffer == nullptr)
	{
		throw WindowsException();
	}

	if (!GetComputerNameExW(ComputerNameNetBIOS, buffer, &buffer_size))
	{
		delete buffer;
		throw WindowsException();
	}

	buffer[buffer_size - 1] = '\0';

	std::wstring computer_name(buffer);
	delete buffer;

	return computer_name;
}

std::wstring SystemInfo::get_username()
{
	unsigned long buffer_size = 0;

	GetUserNameW(nullptr, &buffer_size);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		throw WindowsException();
	}

	wchar_t* buffer = new wchar_t[buffer_size];

	if (buffer == nullptr)
	{
		throw WindowsException();
	}

	if (!GetUserNameW(buffer, &buffer_size))
	{
		delete buffer;
		throw WindowsException();
	}

	buffer[buffer_size - 1] = '\0';
	std::wstring username(buffer);
	delete buffer;

	return username;
}

std::wstring SystemInfo::get_version()
{
	uint32_t version = 0;
	uint32_t major_version = 0;
	uint32_t minor_version = 0;
	uint32_t build = 0;

	version = GetVersion();

	major_version = static_cast<uint32_t>(LOBYTE(LOWORD(version)));
	minor_version = static_cast<uint32_t>(HIBYTE(LOWORD(version)));


	if (version < 0x80000000)
		build = static_cast<uint32_t>(HIWORD(version));

	std::wstring version_string(std::to_wstring(major_version)
		+ L'.' +
		std::to_wstring(minor_version)
		+ L" (" +
		std::to_wstring(build)
		+ L')');

	return version_string;
}

bool SystemInfo::running_on_vm()
{
	BOOL result = false;

	if (!IsNativeVhdBoot(&result))
	{
		throw WindowsException();
	}

	return static_cast<bool>(result);
}

std::wstring SystemInfo::get_firmware_type()
{
	FIRMWARE_TYPE type;

	if (!GetFirmwareType(&type))
	{
		throw WindowsException();
	}

	switch (type)
	{
	case FirmwareTypeBios:
		return L"BIOS";
	case FirmwareTypeUefi:
		return L"UEFI";
	case FirmwareTypeMax:
		return L"MAX";
	case FirmwareTypeUnknown:
		return L"UNKNOWN";
	default:
		throw std::exception("Failed to get firmware type");
	}
}

void SystemInfo::save_system_info()
{
	Logger::Instance().info(L"Saving system info");

	File system_info{ SYSTEM_INFO_FILE };

	system_info.write(L"Computer name: " + SystemInfo::get_computer_name() + L"\n");
	system_info.write(L"User name: " + SystemInfo::get_username() + L"\n");
	system_info.write(L"OS Version: " + SystemInfo::get_version() + L"\n");
	system_info.write(L"Firmware type: " + SystemInfo::get_firmware_type() + L"\n");

	std::wstring running_on_vm = SystemInfo::running_on_vm() ? L"True" : L"False";
	system_info.write(L"Running on VM : " + running_on_vm + L"\n");
}