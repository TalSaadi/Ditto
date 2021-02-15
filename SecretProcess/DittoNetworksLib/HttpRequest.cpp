#include "stdafx.h"
#include "HttpRequest.hpp"


HttpRequest::HttpRequest(const std::string & request) :
	_request(request)
{
}

RequestType HttpRequest::get_request_type() const
{
	std::vector<std::string> http_parts = get_http_header_parts();
	std::string request_type = http_parts[REQUEST_TYPE];

	if (request_type == "GET") return Get;
	else if (request_type == "POST") return Post;
	else if (request_type == "PUT") return Put;
	else if (request_type == "DELETE") return Delete;
	else throw std::exception("Bad request");
}

std::string HttpRequest::get_url() const
{
	return get_http_header_parts()[URL];
}

std::vector<std::string> HttpRequest::get_headers() const
{
	std::vector<std::string> http_parts = get_http_parts();

	if (http_parts.size() < HEADERS)
	{
		return std::vector<std::string>();
	}

	return StringUtils::split(http_parts[HEADERS], std::to_string(StringUtils::NEW_LINE));
}

std::string HttpRequest::get_data() const
{
	std::vector<std::string> http_parts = get_http_parts();

	if (http_parts.size() < DATA)
	{
		return std::string();
	}

	return http_parts[DATA];
}

std::vector<std::string> HttpRequest::get_http_parts() const
{
	std::vector<std::string> http_parts = StringUtils::split(_request, HTTP_NEW_LINE);

	if (http_parts.empty())
	{
		throw std::exception("Bad request");
	}

	return http_parts;
}

std::vector<std::string> HttpRequest::get_http_header_parts() const
{
	std::string http_header = get_http_parts()[HTTP_HEADER];
	std::vector<std::string> http_header_parts = StringUtils::split(http_header, " ");

	if (http_header_parts.empty() || (http_header_parts.size() < HTTP_HEADER_LENGTH))
	{
		throw std::exception("Bad request");
	}

	return http_header_parts;
}