#include "stdafx.h"
#include "RegistryKey.hpp"


RegistryKey::RegistryKey(const HKEY key, const std::wstring& subkey) :
	key_handle(open_key(key, subkey))
{
}

RegistryKey::~RegistryKey()
{
	try 
	{
		if (RegCloseKey(key_handle) != ERROR_SUCCESS)
		{
			throw WindowsException();
		}
	}
	catch (const WindowsException& e)
	{
		std::wcout << e.what() << std::endl;
	}
	catch (...)
	{
		OutputDebugStringW(L"Failed to close key");
	}
}

std::wstring RegistryKey::get_value(const std::wstring & value_name)
{
	unsigned long value_size; 

	LSTATUS result = RegGetValueW(key_handle, nullptr, value_name.c_str(), RRF_RT_ANY, nullptr, nullptr, &value_size);

	if (result != ERROR_SUCCESS)
	{
		throw WindowsException(result);
	}

	wchar_t* data_buffer = reinterpret_cast<wchar_t*>(malloc(value_size));

	if (data_buffer == nullptr)
	{
		throw WindowsException();
	}

	result = RegGetValueW(key_handle, nullptr, value_name.c_str(), RRF_RT_ANY, nullptr, data_buffer, &value_size);

	if (result != ERROR_SUCCESS)
	{
		free(data_buffer);
		throw WindowsException(result);
	}

	std::wstring value_data(data_buffer);
	free(data_buffer);

	return value_data;
}

void RegistryKey::set_value(const std::wstring& value_name, const std::wstring& value_data)
{
	LSTATUS result = RegSetValueExW(key_handle, 
									value_name.c_str(), 
									0,
									REG_SZ, 
									(BYTE*)value_data.c_str(), 
									value_data.size() * sizeof(wchar_t));

	if (result != ERROR_SUCCESS)
	{
		throw WindowsException();
	}
}

HKEY RegistryKey::open_key(const HKEY key, const std::wstring& subkey)
{
	HKEY handle;

	LSTATUS result = RegOpenKeyExW(key, subkey.c_str(), 0, KEY_ALL_ACCESS, &handle);

	if (result != ERROR_SUCCESS)
	{
		throw WindowsException(result);
	}

	return handle;
}
