#pragma once
#include "File.hpp"
#include <string>

// reference additional headers your program requires here
__declspec(dllexport) LRESULT CALLBACK __cdecl KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);