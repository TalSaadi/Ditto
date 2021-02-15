#pragma once
#include "stdafx.h"

namespace HttpResponseCodes
{
	constexpr size_t BAD_REQUEST = 400;
	constexpr size_t OK = 200;
	constexpr size_t NOT_IMPLEMENTED = 501;
}

namespace HttpResponseMessage
{
	constexpr char* BAD_REQUEST = "Bad Request";
	constexpr char* NOT_IMPLEMENTED = "Not Implemented";
	constexpr char* OK = "Ok";
}