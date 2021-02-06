#pragma once
#include "WindowsException.hpp"
#include <Windows.h>
#include <string>
#include <exception>

class File
{
public:
	File(const std::wstring& file_name);
	~File();

public:
	void write(const std::string& content);
	std::string read();

private:
	HANDLE open_file(const std::wstring& file_name);

private:
	HANDLE _handle;
};

