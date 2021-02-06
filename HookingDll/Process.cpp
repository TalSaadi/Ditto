#include "stdafx.h"
#include "Process.hpp"
#include "WindowsException.hpp"


Process::Process(unsigned long pid) :
	m_handle(open_process(pid))
{
}


Process::~Process()
{
	try
	{
		CloseHandle(m_handle);
	}
	catch (...)
	{
		OutputDebugString(L"Failed to close process handle");
	}
}


HANDLE Process::open_process(unsigned long pid)
{
	HANDLE process_handle = OpenProcess(PROCESS_ACCESS, DONT_INHERIT_HANDLE, pid);

	if (process_handle == NULL)
	{
		throw WindowsException();
	}

	return process_handle;
}

HANDLE Process::get_handle()
{
	return m_handle;
}

Thread Process::create_remote_thread(LPTHREAD_START_ROUTINE start_address, void* parameters)
{
	HANDLE handle = CreateRemoteThread(
		m_handle,
		DEFAULT_THREAD_ATTRIBUTES,
		DEFAULT_STACK_SIZE,
		start_address,
		parameters,
		CREATION_FLAGS,
		NO_THREAD_ID);

	if (handle == NULL)
	{
		throw WindowsException();
	}

	return Thread(handle);
}

void* Process::write_process_memory(const std::string & value)
{
	void* value_address = VirtualAllocEx(m_handle, nullptr, value.size() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!value_address)
	{
		throw WindowsException();
	}

	size_t bytes{};

	bool success = WriteProcessMemory(m_handle, value_address, value.c_str(), value.size(), &bytes);

	if (!success || bytes != value.size())
	{
		unsigned long error_code = GetLastError();
		this->delete_process_memory(value_address);
		throw WindowsException(error_code);
	}

	return value_address;
}

void Process::delete_process_memory(void * virtual_address)
{
	VirtualFreeEx(m_handle, virtual_address, 0, MEM_RELEASE);
}

HANDLE Process::map_global_memory(const int value, const std::string& mapping_name)
{
	HANDLE map_handle = CreateFileMappingA(INVALID_HANDLE_VALUE,
		nullptr,
		PAGE_READWRITE,
		0,
		sizeof(value),
		mapping_name.c_str());

	if (!map_handle)
	{
		throw WindowsException();
	}

	void* map_pointer = MapViewOfFile(map_handle, PAGE_READWRITE, 0, 0, sizeof(value));

	if (!map_pointer)
	{
		unsigned long error_code = GetLastError();
		CloseHandle(map_handle);
		throw WindowsException(error_code);
	}

	auto p_hidden_pid = reinterpret_cast<int*>(map_pointer);
	*p_hidden_pid = value;
	UnmapViewOfFile(map_pointer);

	return map_handle;
}

int Process::read_global_memory(const std::string & mapping_name)
{
	HANDLE map_handle = OpenFileMappingA(FILE_MAP_READ, false, mapping_name.c_str());

	if (!map_handle)
	{
		throw WindowsException();
	}

	int g_hidden_pid;
	void* map_pointer = MapViewOfFile(map_handle, PAGE_READWRITE, 0, 0, sizeof(g_hidden_pid));

	if (!map_pointer)
	{
		unsigned long error_code = GetLastError();
		CloseHandle(map_handle);
		throw WindowsException(error_code);
	}

	auto p_hidden_pid = reinterpret_cast<int*>(map_pointer);
	g_hidden_pid = *p_hidden_pid;

	UnmapViewOfFile(map_pointer);
	CloseHandle(map_handle);

	return g_hidden_pid;
}
