#include "logger.h"
#include <string>
#include <iostream>
#include <chrono>

void LOG(const std::string& type, const std::string& message)
{
	std::time_t now = std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now());
	std::string curr_time = std::ctime(&now);
	curr_time.erase(curr_time.size() - 1);
	std::cout << curr_time << " [" << type << "] : "
		<< message << std::endl;
}
