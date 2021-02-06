#pragma once
#include "File.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <map>
#include <memory>
#include <stdio.h>
#include <time.h>

constexpr wchar_t* LOG_FILE_PATH = L"C:\\PerfLogs\\Log.log";
constexpr wchar_t* SEPERATOR = L"  |  ";
constexpr wchar_t* DATE_FORMAT = L"%d/%m/%Y - %H:%M:%S";
constexpr wchar_t* NEW_LINE = L"\n";

enum LevelsEnum {
	INFO_LEVEL,
	WARNING_LEVEL,
	ERROR_LEVEL
};

class Logger
{
public:
	static Logger& Instance();

public:
	void info(const std::wstring& content);
	void warning(const std::wstring& content);
	void error(const std::wstring& content);

private:
	void write(LevelsEnum level, const std::wstring& content);

private:
	File log_file;
	std::map<LevelsEnum, const wchar_t*> levels_map { { LevelsEnum::INFO_LEVEL, L"INFO" }, { LevelsEnum::WARNING_LEVEL, L"WARNING" }, { LevelsEnum::ERROR_LEVEL, L"ERROR" } };

protected:
	Logger();
	~Logger() = default;

public:
	Logger(const Logger&) = delete;
	Logger(Logger&&) = delete;
	Logger& operator=(const Logger&) = delete;
	Logger& operator=(Logger&&) = delete;
};

