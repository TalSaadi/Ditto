#pragma once
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "WindowsException.hpp"

const class TcpSocket
{
public:
	explicit TcpSocket();
	~TcpSocket();

private:
	static SOCKET create_socket();

private:
	SOCKET _socket;
};

