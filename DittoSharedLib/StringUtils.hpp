#pragma once
#include <string>
#include <vector>
#include <sstream>

namespace StringUtils
{
	constexpr char NEW_LINE = '\n';
	constexpr wchar_t NEW_LINE_W = L'\n';
	constexpr char SPACE = ' ';

	std::vector<std::string> split(const std::string& str, const std::string& delimiter);
}