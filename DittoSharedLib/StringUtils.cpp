#include "stdafx.h"
#include "StringUtils.hpp"

std::vector<std::string> StringUtils::split(const std::string & str, const std::string& delimiter)
{
	std::vector<std::string> parts;

	size_t index = str.find(delimiter);

	if (index == std::string::npos)
	{
		return parts;
	}

	std::string token = str.substr(0, index);
	parts.push_back(token);
	token = str.substr(index + 1 + delimiter.length(), str.length() - 1);
	parts.push_back(token);

	return parts;
}
