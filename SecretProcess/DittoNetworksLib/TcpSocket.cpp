#include "stdafx.h"
#include "TcpSocket.hpp"

TcpSocket::TcpSocket() :
	_socket(create_socket())
{
}

TcpSocket::TcpSocket(SOCKET socket) :
	_socket(socket)
{
}

TcpSocket::~TcpSocket()
{
	try
	{
		close();
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

TcpSocket TcpSocket::accept() const
{
	SOCKET socket = ::accept(_socket, nullptr, nullptr);

	if (socket == INVALID_SOCKET) 
	{
		throw WindowsException(WSAGetLastError());
	}
	
	return TcpSocket(socket);
}

void TcpSocket::bind(const std::string & address, const int port) const
{
	sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr(address.c_str());
	socket_address.sin_port = htons(port);

	int result = ::bind(_socket, (SOCKADDR*)(&socket_address), sizeof(socket_address));

	if (result == SOCKET_ERROR)
	{
		throw WindowsException(WSAGetLastError());
	}
}

void TcpSocket::listen(const int connections) const
{
	if (::listen(_socket, connections) == SOCKET_ERROR)
	{
		throw WindowsException(WSAGetLastError());
	}
}

void TcpSocket::close() const
{
	int result = closesocket(_socket);

	if (result == SOCKET_ERROR)
	{
		throw WindowsException(WSAGetLastError());
	}
}

void TcpSocket::connect(const std::string & address, const int port) const
{
	sockaddr_in socket_address;
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr(address.c_str());
	socket_address.sin_port = htons(port);

	int result = ::connect(_socket, (SOCKADDR*)&socket_address, sizeof(socket_address));

	if (result == SOCKET_ERROR) 
	{
		throw WindowsException(WSAGetLastError());
	}
}

int TcpSocket::send(const std::string& data) const
{
	int result = ::send(_socket, data.c_str(), static_cast<int>(data.size()), 0);

	if (result == SOCKET_ERROR)
	{
		throw WindowsException(WSAGetLastError());
	}

	return result;
}

std::string TcpSocket::recv(const size_t length, size_t* bytes_recv) const
{
	char* recv_buffer = reinterpret_cast<char*>(malloc(length));

	if (recv_buffer == nullptr)
	{
		throw WindowsException();
	}

	int result = ::recv(_socket, recv_buffer, static_cast<int>(length), 0);

	if (result == SOCKET_ERROR)
	{
		free(recv_buffer);
		throw WindowsException(WSAGetLastError());
	}

	*bytes_recv = result;
	return recv_buffer;
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
