#pragma once
#include <Windows.h>
#include <string>

const class FileInfo
{
public:
	explicit FileInfo(WIN32_FIND_DATA file_data);
	~FileInfo() = default;

public:
	std::wstring get_file_name() const;
	uint64_t get_file_size() const;
	bool is_directory() const;

private:
	WIN32_FIND_DATA file_data;
};

