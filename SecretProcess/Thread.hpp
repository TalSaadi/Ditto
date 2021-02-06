#pragma once
#include "WindowsException.hpp"
#include <Windows.h>

constexpr unsigned long THREAD_ACCESS = THREAD_ALL_ACCESS;
constexpr unsigned long RUN_THREAD_FAILED = -1;
constexpr bool DONT_INHERIT_HANDLE = false;

class Thread
{
public:
	Thread(unsigned long tid);
	Thread(HANDLE handle);
	Thread(LPTHREAD_START_ROUTINE function, void* parameter);
	~Thread();

public:
	HANDLE get_handle();
	void run();
	void wait();

private:
	HANDLE open_thread(unsigned long tid);
	HANDLE create_thread(LPTHREAD_START_ROUTINE function, void* parameter);

private:
	HANDLE m_handle;
};

