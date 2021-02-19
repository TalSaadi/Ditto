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

std::wstring SystemInfo::get_keyboard_layout()
{
	HWND hwnd = GetForegroundWindow();

	if (!hwnd)
	{
		throw WindowsException();
	}

	uint32_t thread_id = GetWindowThreadProcessId(hwnd, nullptr);
	HKL current_layout = GetKeyboardLayout(thread_id);
	LANGID language = PRIMARYLANGID(current_layout);

	wchar_t buffer[LOCALE_NAME_MAX_LENGTH];

	if (!LCIDToLocaleName(language, buffer, LOCALE_NAME_MAX_LENGTH, 0))
	{
		throw WindowsException();
	}

	return buffer;
}

void SystemInfo::save_system_info()
{
	Logger::Instance().info(L"Saving system info");

	File system_info{ SYSTEM_INFO_FILE };

	system_info.write(L"Computer name: " + SystemInfo::get_computer_name() + StringUtils::NEW_LINE_W);
	system_info.write(L"User name: " + SystemInfo::get_username() + StringUtils::NEW_LINE_W);
	system_info.write(L"Keyboard language: " + SystemInfo::get_keyboard_layout() + StringUtils::NEW_LINE_W);
	system_info.write(L"OS Version: " + SystemInfo::get_version() + StringUtils::NEW_LINE_W);
	system_info.write(L"Firmware type: " + SystemInfo::get_firmware_type() + StringUtils::NEW_LINE_W);

	std::wstring running_on_vm = SystemInfo::running_on_vm() ? L"True" : L"False";
	system_info.write(L"Running on VM : " + running_on_vm + StringUtils::NEW_LINE_W);
}