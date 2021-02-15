#pragma once
#pragma warning(disable:4996) 
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "WindowsException.hpp"

const class TcpSocket
{
public:
	explicit TcpSocket();
	explicit TcpSocket(SOCKET socket);
	~TcpSocket();

public:
	TcpSocket accept() const;
	void bind(const std::string& address, const int port) const;
	void listen(const int connections) const;
	void close() const;
	void connect(const std::string& address, const int port) const;
	int send(const std::string& data) const;
	std::string recv(const size_t length, size_t* bytes_recv) const;

private:
	static SOCKET create_socket();

private:
	SOCKET _socket;
};