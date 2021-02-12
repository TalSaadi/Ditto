#pragma once
#include "WindowsException.hpp"
#include "File.hpp"
#include <Windows.h>

namespace Bitmap
{
	PBITMAPINFO create_bitmap_info_struct(HBITMAP bitmap_handle);
	uint16_t convert_color_format_to_bits_count(BITMAP bitmap);
	void create_bitmap_file(const std::wstring& file_name, PBITMAPINFO bitmap_info, HBITMAP bitmap_handle, HDC dc_handle);
};

