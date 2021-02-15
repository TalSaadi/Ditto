#pragma once
#include "StringUtils.hpp"
#include <string>
#include <vector>

enum RequestType
{
	Get, 
	Post,
	Put,
	Delete
};

constexpr char* HTTP_NEW_LINE = "\r\n";
constexpr uint16_t HTTP_HEADER = 0;
constexpr uint16_t HEADERS = 1;
constexpr uint16_t DATA = 2;
constexpr uint16_t HTTP_HEADER_LENGTH = 3;
constexpr uint16_t REQUEST_TYPE = 0;
constexpr uint16_t URL = 1;

const class HttpRequest
{
public:
	explicit HttpRequest(const std::string& request);
	~HttpRequest() = default;

public: 
	RequestType get_request_type() const;
	std::string get_url() const;
	std::vector<std::string> get_headers() const;
	std::string get_data() const;

private:
	std::vector<std::string> get_http_parts() const;
	std::vector<std::string> get_http_header_parts() const;

private:
	std::string _request;
};

