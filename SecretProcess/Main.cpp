#include "pch.h"
#include "Process.hpp"
#include "WindowsException.hpp"
#include "Logger.hpp"
#include "SystemUtils.hpp"
#include <exception>
#include <iostream>
#include <chrono>

int main()
{
	try 
	{
		Thread thread{ reinterpret_cast<LPTHREAD_START_ROUTINE>(&SystemUtils::hide_from_task_manager), nullptr };
		thread.run();
		thread.wait();
	}
	catch (WindowsException exp)
	{
		std::wcout << exp.what() << std::endl;
	}
	catch (std::exception exp)
	{
		std::wcout << exp.what() << std::endl;
	}
	catch (...)
	{
		OutputDebugString(L"Unexpected exception");
	}
}