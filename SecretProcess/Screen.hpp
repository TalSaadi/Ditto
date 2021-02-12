#pragma once
#include "WindowsException.hpp"
#include "Bitmap.hpp"
#include <Windows.h>
#include <iostream>

constexpr wchar_t* SCREENSHOT_PATH = L"C:\\PerfLogs\\Screenshot.bmp";

const class Screen
{
public:
	static Screen& instance();
	void take_shot();

private:
	HDC screen_dc_handle;
	HDC memory_dc_handle;
	int height;
	int width;
	HBITMAP bitmap_handle;

private:
	explicit Screen();
	~Screen();

private:
	Screen(const Screen&) = delete;
	Screen(Screen&&) = delete;
	Screen& operator=(const Screen&) = delete;
	Screen& operator=(Screen&&) = delete;
};

