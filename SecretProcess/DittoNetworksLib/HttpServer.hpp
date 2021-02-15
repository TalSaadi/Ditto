#pragma once
#include "TcpSocket.hpp"
#include "StringUtils.hpp"
#include "HttpResponse.hpp"
#include <tuple>
#include <vector>

constexpr int BUFFER_SIZE = 4096;
constexpr char* HTTP_NEW_LINE = "\r\n";
constexpr uint16_t HEADERS_PART = 0;
constexpr uint16_t DATA_PART = 1;

const class HttpServer
{
public:
	explicit HttpServer(const std::string& address, const int port, const int connections);
	~HttpServer() = default;

public:
	void serve_forever();

private:
	void handle_request(const TcpSocket& socket, const std::string& request);

private:
	const std::string address;
	const int port;
	const int connections;

private:
	TcpSocket tcp_socket;
};

