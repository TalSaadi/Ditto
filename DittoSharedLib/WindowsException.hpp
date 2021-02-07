#pragma once
#include <string>
#include <Windows.h>

constexpr unsigned long FORMAT_MESSAGE_FLAGS = (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS);

const class WindowsException
{
public:
	explicit WindowsException();
	WindowsException(unsigned long error_code);
	~WindowsException();

public:
	std::wstring what() const;

private:
	std::wstring get_error_message(unsigned long error_code);

private:
	std::wstring error_message;
};

