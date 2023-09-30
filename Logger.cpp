#include "Logger.h"

#include <iostream>

Logger::Logger(const std::string& file_name)
{
	_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		_file.open(file_name, std::ios::in | std::ios::out | std::ios::app);
	}
	catch (std::fstream::failure e) 
	{
		std::cerr << e.what();
	}	
}

Logger::~Logger()
{
	try
	{
		_file.close();
	}
	catch (std::fstream::failure e)
	{
		std::cerr << e.what();
	}
}

void Logger::Write(const std::string& data)
{
	std::unique_lock lock(_mutex);
	if (_file.is_open())
	{
		try
		{
			_file << data;
			_file.flush();
		}
		catch (std::fstream::failure e)
		{
			std::cerr << e.what();
		}
	}
}

std::string Logger::Read()
{
	std::string res;
	std::unique_lock lock(_mutex);
	if (_file.is_open())
	{
		try
		{
			_file.seekg(0);
			std::getline(_file, res, '\0');
		}
		catch (std::fstream::failure e)
		{
			std::cerr << e.what();
		}
	}
	return res;
}
