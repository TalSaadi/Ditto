#include "stdafx.h"
#include "Thread.hpp"


Thread::Thread(unsigned long tid) :
	m_handle(open_thread(tid))
{
}

Thread::Thread(HANDLE thread_handle) :
	m_handle(thread_handle)
{
}

Thread::Thread(LPTHREAD_START_ROUTINE function, void* parameter) :
	m_handle(create_thread(function, parameter))
{
}

Thread::~Thread()
{
	try
	{
		CloseHandle(m_handle);
	}
	catch (...)
	{
		OutputDebugString(L"Failed to close handle");
	}
}

HANDLE Thread::open_thread(unsigned long tid)
{
	HANDLE thread_handle = OpenThread(THREAD_ACCESS, DONT_INHERIT_HANDLE, tid);

	if (thread_handle == NULL)
	{
		throw WindowsException();
	}

	return thread_handle;
}

HANDLE Thread::create_thread(LPTHREAD_START_ROUTINE function, void* parameter)
{
	HANDLE thread_handle = CreateThread(NULL, 0, function, parameter, CREATE_SUSPENDED, NULL);

	if (thread_handle == NULL)
	{
		throw WindowsException();
	}

	return thread_handle;
}

HANDLE Thread::get_handle()
{
	return m_handle;
}

void Thread::run()
{
	unsigned long count = ResumeThread(m_handle);

	if (count == RUN_THREAD_FAILED)
	{
		throw WindowsException();
	}
}

void Thread::wait()
{
	WaitForSingleObject(m_handle, INFINITE);
}
