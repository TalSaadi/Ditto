#pragma once
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <tuple>
#include "WindowsException.hpp"

const class TcpSocket
{
public:
	explicit TcpSocket();
	~TcpSocket();

public:
	std::tuple<TcpSocket, std::wstring> accept();
	void bind(const std::string& address, const int port);
	void listen(const int connections);
	void close();
	void connect(const std::string& address, const int port);
	int send(const std::string& data);
	std::string recv(const size_t length);

private:
	static SOCKET create_socket();

private:
	SOCKET _socket;
};