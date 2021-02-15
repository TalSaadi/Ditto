#include "pch.h"
#include "Directory.hpp"


Directory::Directory(const std::wstring& directory_name) :
	file_handle(open_directory(directory_name + WILDCARD))
{
}

Directory::~Directory()
{
	try
	{
		FindClose(file_handle);
	}
	catch (...)
	{
		OutputDebugStringW(L"Failed to close directory");
	}
}

HANDLE Directory::open_directory(const std::wstring& directory_name)
{
	HANDLE handle = FindFirstFileW(directory_name.c_str(), &file_data);

	if (handle == INVALID_HANDLE_VALUE)
	{
		throw WindowsException();
	}

	return handle;
}

FileInfo Directory::get_current_file() const
{
	return FileInfo(file_data);
}

bool Directory::get_next_file()
{
	if (!FindNextFileW(file_handle, &file_data))
	{
		uint32_t error_code = GetLastError();

		if (error_code == ERROR_NO_MORE_FILES)
		{
			return false;
		}

		throw WindowsException();
	}

	return true;
}
