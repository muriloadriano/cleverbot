#include "logger.h"

#include <iostream>
#include <chrono>

void LOG(const std::string& type, const std::string& message)
{
	std::time_t now = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	
	std::cout << std::ctime(&now) << " [" << type << "] : "
		<< message << std::endl;
}