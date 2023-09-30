#pragma once

#include <string>
#include <shared_mutex>
#include <fstream>

class Logger
{
public:
	Logger(const std::string&);
	~Logger();
	void Write(const std::string&);
	std::string Read();
private:
	std::shared_mutex _mutex;
	std::fstream _file;
};

