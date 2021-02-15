#include "stdafx.h"
#include "HttpResponse.hpp"

std::string HttpResponse::bad_request()
{
	return make_response(HttpResponseCodes::BAD_REQUEST, HttpResponseMessage::BAD_REQUEST, "");
}

std::string HttpResponse::not_implemented()
{
	return make_response(HttpResponseCodes::NOT_IMPLEMENTED, HttpResponseMessage::NOT_IMPLEMENTED, "");
}

std::string HttpResponse::ok()
{
	return make_response(HttpResponseCodes::OK, HttpResponseMessage::OK, "");
}

std::string HttpResponse::make_response(const size_t code, const std::string & message, const std::string & data)
{
	std::string response;

	response += HTTP_VERSION;
	response += StringUtils::SPACE + std::to_string(code) + StringUtils::SPACE;
	response += message + StringUtils::NEW_LINE;

	return response;
}