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
