#pragma once
#include "WindowsException.hpp"
#include <Windows.h>
#include <string>
#include <winternl.h>



namespace IATHooking
{
	class IATHooking
	{
	public:
		IATHooking(const std::string& module, const std::string& function_name, void* hook);
		~IATHooking();

	public:
		void* get_original_function();

	private:
		PIMAGE_THUNK_DATA _iat_entry;
		void* _original_function;
	};
}
