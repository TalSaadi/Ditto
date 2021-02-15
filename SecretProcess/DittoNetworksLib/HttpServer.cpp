#include "stdafx.h"
#include "HttpServer.hpp"

HttpServer::HttpServer(const std::string& address, const int port, const int connections) :
	address(address),
	port(port),
	connections(connections)
{
}

void HttpServer::serve_forever()
{
	tcp_socket.bind(address, port);
	tcp_socket.listen(connections);

	while (true)
	{
		TcpSocket connection = tcp_socket.accept();
		std::string request;
		size_t bytes_recv;

		while (true)
		{
			request += connection.recv(BUFFER_SIZE, &bytes_recv);

			if (bytes_recv < BUFFER_SIZE)
			{
				break;
			}
		}

		handle_request(connection, request);
		connection.close();
	}
}

void HttpServer::handle_request(const TcpSocket& socket, const std::string& request)
{
	std::vector<std::string> http_parts = StringUtils::split(request, HTTP_NEW_LINE);

	if (http_parts.empty())
	{
		socket.send(HttpResponse::bad_request());
		return;
	}

	std::cout << http_parts[HEADERS_PART] << std::endl;
	std::cout << http_parts[DATA_PART] << std::endl;

	socket.send(HttpResponse::ok());
}
