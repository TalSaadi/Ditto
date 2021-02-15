#pragma once
#include "HttpResponseCodes.hpp"
#include "StringUtils.hpp"
#include <string>

constexpr char* HTTP_VERSION = "HTTP/1.1";

namespace HttpResponse
{
	std::string bad_request();
	std::string ok();
	std::string make_response(const size_t code, const std::string& message, const std::string& data);
}