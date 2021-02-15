#pragma once
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "WindowsException.hpp"
#include <iostream>

constexpr int VERSION = 2;

const class WinSock
{
public:
	explicit WinSock();
	~WinSock();

private:
	WSADATA winsock_data;
};

