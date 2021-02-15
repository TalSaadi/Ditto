#include "pch.h"
#include "FileInfo.hpp"


FileInfo::FileInfo(WIN32_FIND_DATA file_data) :
	file_data(file_data)
{
}

std::wstring FileInfo::get_file_name() const
{
	return file_data.cFileName;
}

uint64_t FileInfo::get_file_size() const
{
	uint64_t file_size = file_data.nFileSizeHigh;
	file_size <<= sizeof(file_data.nFileSizeHigh) * 8;
	file_size |= file_data.nFileSizeLow;

	return file_size;
}

bool FileInfo::is_directory() const
{
	return (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}
