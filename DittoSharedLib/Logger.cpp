#include "stdafx.h"
#include "Logger.hpp"


Logger::Logger() :
	log_file(LOG_FILE_PATH)
{
}

Logger& Logger::Instance()
{
	static Logger logger;

	return logger;
}

void Logger::info(const std::wstring& content)
{
	this->write(LevelsEnum::INFO_LEVEL, content);
}

void Logger::warning(const std::wstring& content)
{
	this->write(LevelsEnum::WARNING_LEVEL, content);
}

void Logger::error(const std::wstring& content)
{
	this->write(LevelsEnum::ERROR_LEVEL, content);
}

void Logger::write(LevelsEnum level, const std::wstring& content)
{
	std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm timeinfo;
	wchar_t buffer[80];
	time(&tt);
	localtime_s(&timeinfo, &tt);
	wcsftime(buffer, 80, DATE_FORMAT, &timeinfo);

	log_file.write(buffer);
	log_file.write(SEPERATOR);
	log_file.write(levels_map[level]);
	log_file.write(SEPERATOR);
	log_file.write(content);
	log_file.write(std::to_wstring(StringUtils::NEW_LINE_W));
}