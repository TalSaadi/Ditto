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

void File::write(const std::wstring & content)
{
	this->set_file_pointer(FILE_END);

	unsigned long bytes_written;

	if (!WriteFile(_handle, content.c_str(), static_cast<uint32_t>(content.size() * sizeof(wchar_t)), &bytes_written, NULL))
	{
		throw WindowsException();
	}

	if (bytes_written != (content.size() * sizeof(wchar_t)))
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
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (file_handle == INVALID_HANDLE_VALUE)
	{
		throw WindowsException();
	}

	return file_handle;
}

void File::set_file_pointer(uint32_t move_method)
{
	unsigned long moved = SetFilePointer(_handle, 0l, nullptr, move_method);

	if (moved == INVALID_SET_FILE_POINTER)
	{
		throw WindowsException();
	}
}
