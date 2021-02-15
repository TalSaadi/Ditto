#include "stdafx.h"
#include "TcpSocket.hpp"

TcpSocket::TcpSocket() :
	_socket(create_socket())
{
}

TcpSocket::~TcpSocket()
{
	try
	{
		int result = closesocket(_socket);

		if (result == SOCKET_ERROR)
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
		OutputDebugStringW(L"Failed to close socket");
	}
}

SOCKET TcpSocket::create_socket()
{
	SOCKET socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (socket_fd == INVALID_SOCKET)
	{
		throw WindowsException(WSAGetLastError());
	}

	return socket_fd;
}
