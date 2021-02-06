#pragma once
#include "Thread.hpp"
#include <Windows.h>

constexpr unsigned long PROCESS_ACCESS = PROCESS_ALL_ACCESS;
constexpr LPSECURITY_ATTRIBUTES DEFAULT_THREAD_ATTRIBUTES = NULL;
constexpr size_t DEFAULT_STACK_SIZE = 0;
constexpr void* NO_PARAMETERS = NULL;
constexpr unsigned long CREATION_FLAGS = CREATE_SUSPENDED;
constexpr unsigned long NO_THREAD_ID = NULL;

class Process
{
public:
	Process(unsigned long pid);
	~Process();

public:
	HANDLE get_handle();
	Thread create_remote_thread(LPTHREAD_START_ROUTINE start_address, void* parameters);
	void* write_process_memory(const std::string& value);
	void delete_process_memory(void* virtual_address);
	static HANDLE map_global_memory(const int value, const std::string& mapping_name);
	static int read_global_memory(const std::string& mapping_name);

private:
	HANDLE open_process(unsigned long pid);

private:
	HANDLE m_handle;
};

