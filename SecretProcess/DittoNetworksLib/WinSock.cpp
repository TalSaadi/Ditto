#include "stdafx.h"
#include "WinSock.hpp"

WinSock::WinSock()
{
	int error_code = WSAStartup(MAKEWORD(VERSION, VERSION), &winsock_data);

	if (error_code != 0)
	{
		throw WindowsException(error_code);
	}

	if (LOBYTE(winsock_data.wVersion) != VERSION || HIBYTE(winsock_data.wVersion) != VERSION)
	{
		WSACleanup();
		throw std::exception("Could not find a usable version of Winsock.dll");
	}
}

WinSock::~WinSock()
{
	try
	{
		int error_code = WSACleanup();

		if (error_code == SOCKET_ERROR)
		{
			throw WindowsException(WSAGetLastError());
		}
	}
	catch (const WindowsException& e)
	{
		std::wcout << e.what() << std::endl;
	}
	catch (...)
	{
		OutputDebugStringW(L"Failed to clean wsa");
	}
}
