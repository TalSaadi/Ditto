#pragma once
#include "TcpSocket.hpp"
#include "StringUtils.hpp"
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"
#include "Logger.hpp"
#include <tuple>
#include <vector>

constexpr int BUFFER_SIZE = 4096;

const class HttpServer
{
public:
	explicit HttpServer(const std::string& address, const int port, const int connections);
	~HttpServer() = default;

public:
	void serve_forever();

private:
	void handle_request(const TcpSocket& socket, const std::string& request);
	void handle_get_request(const TcpSocket& socket, const HttpRequest& http_request) const;
	void handle_post_request(const TcpSocket& socket, const HttpRequest& http_request) const;
	void handle_put_request(const TcpSocket& socket, const HttpRequest& http_request) const;
	void handle_delete_request(const TcpSocket& socket, const HttpRequest& http_request) const;

private:
	const std::string address;
	const int port;
	const int connections;

private:
	TcpSocket tcp_socket;
};

