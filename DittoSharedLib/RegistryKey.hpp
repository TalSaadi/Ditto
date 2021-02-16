#pragma once
#include "WindowsException.hpp"
#include <iostream>
#include <Windows.h>

constexpr wchar_t* STARTUP_KEY = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
constexpr wchar_t* MS_CONFIG = L"MsConfig";

const class RegistryKey
{
public:
	explicit RegistryKey(const HKEY key, const std::wstring& subkey);
	~RegistryKey();

public:
	std::wstring get_value(const std::wstring& value_name);
	void set_value(const std::wstring& value_name, const std::wstring& value_data);

private:
	static HKEY open_key(const HKEY key, const std::wstring& subkey);

private:
	HKEY key_handle;
};

