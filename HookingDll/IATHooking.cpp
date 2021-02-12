#include "stdafx.h"
#include "IATHooking.hpp"
#include "File.hpp"


IATHooking::IATHooking(const std::string& module, const std::string & function_name, void * hook) :
	_iat_entry(nullptr),
	_original_function(nullptr)
{
	auto tsk_mgr_module = reinterpret_cast<unsigned char*>(GetModuleHandleA(module.c_str()));

	if (!tsk_mgr_module)
	{
		throw WindowsException();
	}
	auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(tsk_mgr_module);
	auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(tsk_mgr_module + dos_header->e_lfanew);
	auto import_descriptor = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(tsk_mgr_module + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	for (import_descriptor; import_descriptor->Name; import_descriptor++)
	{
		PIMAGE_THUNK_DATA ilt_entry = reinterpret_cast<PIMAGE_THUNK_DATA>(tsk_mgr_module + import_descriptor->OriginalFirstThunk);
		PIMAGE_THUNK_DATA iat_entry = reinterpret_cast<PIMAGE_THUNK_DATA>(tsk_mgr_module + import_descriptor->FirstThunk);

		for (ilt_entry, iat_entry; ilt_entry->u1.AddressOfData; ilt_entry++, iat_entry++)
		{
			auto raw_ilt_entry = *reinterpret_cast<unsigned long long*>(ilt_entry);
			if (!(raw_ilt_entry & 0x8000000000000000))
			{
				std::string import_name(reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(tsk_mgr_module + ilt_entry->u1.AddressOfData)->Name);
				if (function_name == import_name)
				{
					_iat_entry = iat_entry;

					DWORD old_protect;
					VirtualProtect(&iat_entry->u1.Function, sizeof(void*), PAGE_READWRITE, &old_protect);

					_original_function = reinterpret_cast<void*>(InterlockedExchange64(
						reinterpret_cast<volatile long long*>(&iat_entry->u1.Function),
						reinterpret_cast<long long>(hook)
					));

					VirtualProtect(&iat_entry->u1.Function, sizeof(void*), old_protect, &old_protect);
						
					return;
				}
			}
		}
	}
}

IATHooking::~IATHooking()
{
	try
	{
		if (_iat_entry && _original_function)
		{
			DWORD old_protect;
			VirtualProtect(&_iat_entry->u1.Function, sizeof(void*), PAGE_READWRITE, &old_protect);

			InterlockedExchange64(
				reinterpret_cast<volatile long long*>(&_iat_entry->u1.Function),
				reinterpret_cast<long long>(_original_function)
			);

			VirtualProtect(&_iat_entry->u1.Function, sizeof(void*), old_protect, &old_protect);
		}
	}
	catch (...) 
	{
		OutputDebugString(L"Failed to release hook");
	}
}

void * IATHooking::get_original_function()
{
	return _original_function;
}