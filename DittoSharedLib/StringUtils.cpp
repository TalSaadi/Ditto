#include "stdafx.h"
#include "StringUtils.hpp"

std::vector<std::string> StringUtils::split(const std::string & str, const std::string& delimiter)
{
	std::vector<std::string> parts;
	std::string copy_str = str;

	for (size_t index = copy_str.find(delimiter); index != std::string::npos; index = copy_str.find(delimiter))
	{
		std::string token = copy_str.substr(0, index);
		parts.push_back(token);
		copy_str = copy_str.substr(index + delimiter.length(), copy_str.length() - 1);
	}

	if (copy_str.size() != str.size())
	{
		parts.push_back(copy_str);
	}

	return parts;
}
