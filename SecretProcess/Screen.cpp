#include "pch.h"
#include "Screen.hpp"


Screen& Screen::instance()
{
	static Screen screen;

	return screen;
}

Screen::Screen()
{
	screen_dc_handle = GetDC(nullptr);

	if (!screen_dc_handle)
	{
		throw WindowsException();
	}

	memory_dc_handle = CreateCompatibleDC(screen_dc_handle);

	if (!memory_dc_handle)
	{
		ReleaseDC(nullptr, screen_dc_handle);
		throw WindowsException();
	}

	width = GetDeviceCaps(screen_dc_handle, HORZRES);
	height = GetDeviceCaps(screen_dc_handle, VERTRES);

	if ((width <= 0) || (height <= 0))
	{
		DeleteDC(memory_dc_handle);
		ReleaseDC(nullptr, screen_dc_handle);
		throw std::exception("Invalid height or width");
	}
}

Screen::~Screen()
{
	try
	{
		DeleteDC(memory_dc_handle);
		ReleaseDC(nullptr, screen_dc_handle);

		if (bitmap_handle)
		{
			DeleteObject(bitmap_handle);
		}
	}
	catch (const WindowsException& e)
	{
		std::wcout << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::wcout << e.what() << std::endl;
	}
	catch (...)
	{
		OutputDebugStringW(L"Unable to release screen");
	}
}

void Screen::take_shot()
{
	bitmap_handle = CreateCompatibleBitmap(screen_dc_handle, width, height);

	if (!bitmap_handle)
	{
		throw WindowsException();
	}

	HBITMAP old_bitmap = static_cast<HBITMAP>(SelectObject(memory_dc_handle, bitmap_handle));

	if (!old_bitmap)
	{
		DeleteObject(bitmap_handle);
		throw WindowsException();
	}

	if (!BitBlt(memory_dc_handle, 0, 0, width, height, screen_dc_handle, 0, 0, SRCCOPY))
	{
		DeleteObject(bitmap_handle);
		DeleteObject(old_bitmap);
		throw WindowsException();
	}

	bitmap_handle = static_cast<HBITMAP>(SelectObject(memory_dc_handle, old_bitmap));

	if (!bitmap_handle)
	{
		DeleteObject(old_bitmap);
		throw WindowsException();
	}

	DeleteObject(old_bitmap);

	PBITMAPINFO bitmap_info = Bitmap::create_bitmap_info_struct(bitmap_handle);
	Bitmap::create_bitmap_file(SCREENSHOT_PATH, bitmap_info, bitmap_handle, screen_dc_handle);
}