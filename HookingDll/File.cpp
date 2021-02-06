#include "stdafx.h"
#include "File.hpp"

File::File(const std::wstring & file_name) :
	_handle(open_file(file_name))
{
}

File::~File()
{
	try
	{
		if (_handle)
		{
			CloseHandle(_handle);
		}
	}
	catch (...)
	{
		OutputDebugString(L"Failed to close file handle");
	}
}

void File::write(const std::string & content)
{
	unsigned long bytes_written;

	if (!WriteFile(_handle, content.c_str(), content.size(), &bytes_written, NULL))
	{
		throw WindowsException();
	}

	if (bytes_written != content.size())
	{
		throw std::exception("Failed to write all the data");
	}
}

std::string File::read()
{
	char buffer[5];
	unsigned long bytes_read;

	if (!ReadFile(_handle, buffer, 4, &bytes_read, NULL))
	{
		throw WindowsException();
	}

	if (bytes_read > 0 && bytes_read <= 4)
	{
		buffer[bytes_read] = '\0';

		return buffer;
	}
	else
	{
		throw std::exception("Failed to read all data");
	}
}

HANDLE File::open_file(const std::wstring & file_name)
{
	HANDLE file_handle = CreateFileW(file_name.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		throw WindowsException();
	}

	return file_handle;
}
