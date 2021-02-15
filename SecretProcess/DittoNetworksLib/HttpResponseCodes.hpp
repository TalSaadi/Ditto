#pragma once
#include "stdafx.h"

namespace HttpResponseCodes
{
	constexpr size_t BAD_REQUEST = 400;
	constexpr size_t OK = 200;
}

namespace HttpResponseMessage
{
	constexpr char* BAD_REQUEST = "BAD_REQUEST";
	constexpr char* OK = "OK";
}