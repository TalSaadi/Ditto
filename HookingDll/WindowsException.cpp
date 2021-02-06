#include "stdafx.h"
#include "WindowsException.hpp"


WindowsException::WindowsException() :
	error_message(get_error_message(GetLastError()))
{
}

WindowsException::WindowsException(unsigned long error_code) :
	error_message(get_error_message(error_code))
{
}

WindowsException::~WindowsException()
{
}

std::wstring WindowsException::what()
{
	return error_message;
}

std::wstring WindowsException::get_error_message(unsigned long error_code)
{
	LPVOID lpMsgBuf;

	FormatMessageW(FORMAT_MESSAGE_FLAGS,
		NULL,
		error_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(wchar_t*)&lpMsgBuf,
		0,
		NULL);

	std::wstring message = std::wstring((wchar_t*)lpMsgBuf);

	LocalFree(lpMsgBuf);

	return message;
}