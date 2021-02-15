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
	std::wcout << L"<<<<<<<<<<<<<<<<<<<<<< DITTO SERVER IS UP >>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	tcp_socket.bind(address, port);
	tcp_socket.listen(connections);
	std::cout << "Listening on " << address << ":" << std::to_string(port) << std::endl;

	while (true)
	{
		std::string request;
		size_t bytes_recv;

		TcpSocket connection = tcp_socket.accept();
		std::wcout << L"New connection was accepted" << std::endl;

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
	HttpRequest http_request(request);

	try
	{
		RequestType request_type = http_request.get_request_type();

		switch (request_type)
		{
		case Get:
			handle_get_request(socket, http_request);
			break;
		case Post:
			handle_post_request(socket, http_request);
			break;
		case Put:
			handle_put_request(socket, http_request);
			break;
		case Delete:
			handle_delete_request(socket, http_request);
			break;
		default:
			socket.send(HttpResponse::not_implemented());
			break;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		socket.send(HttpResponse::bad_request());
	}
}

void HttpServer::handle_get_request(const TcpSocket& socket, const HttpRequest& http_request) const
{
	std::string url = http_request.get_url();
	std::vector<std::string> headers = http_request.get_headers();
	std::string data = http_request.get_data();

	socket.send(HttpResponse::not_implemented());
}

void HttpServer::handle_post_request(const TcpSocket& socket, const HttpRequest& http_request) const
{
	socket.send(HttpResponse::not_implemented());
}

void HttpServer::handle_put_request(const TcpSocket& socket, const HttpRequest& http_request) const
{
	socket.send(HttpResponse::not_implemented());
}

void HttpServer::handle_delete_request(const TcpSocket& socket, const HttpRequest& http_request) const
{
	socket.send(HttpResponse::not_implemented());
}
