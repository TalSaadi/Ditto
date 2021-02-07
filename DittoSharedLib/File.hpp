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
	void write(const std::wstring& content);
	std::string read();

private:
	HANDLE open_file(const std::wstring& file_name);
	void set_file_pointer(uint32_t move_method);

private:
	HANDLE _handle;

public:
	File(const File&) = delete;
	File(File&&) = delete;
	File& operator=(const File&) = delete;
	File& operator=(File&&) = delete;
};

