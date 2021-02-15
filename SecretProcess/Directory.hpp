#pragma once
#include "WindowsException.hpp"
#include "FileInfo.hpp"
#include <string>
#include <Windows.h>

constexpr wchar_t* WILDCARD = L"\\*";

const class Directory
{
public:
	explicit Directory(const std::wstring& directory_name);
	~Directory();

public:
	FileInfo get_current_file() const;
	bool get_next_file();

private:
	HANDLE open_directory(const std::wstring& directory_name);

private:
	HANDLE file_handle;
	WIN32_FIND_DATA file_data;
};

