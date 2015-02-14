#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include "bot.h"

using namespace std;

int main()
{
	try {
		// Starts a new cleverbot with the variables set in the file 'config'
		clever_bot::bot bot("config");

		// Sets its name and joins a channel
		//bot.nick("botche");
      		//bot.join("#murilo");
		
		// Read handlers example (will be improved soon)
		bot.add_read_handler([&bot](const std::string& m) {
			std::istringstream iss(m);
			std::string from, type, to, msg;
			
			iss >> from >> type >> to >> msg;
			
			if (msg == ":!time") {
				std::time_t now = std::chrono::system_clock::to_time_t(
					std::chrono::system_clock::now());
					
				bot.message(to, std::ctime(&now));
			}
		});

		bot.add_read_handler([&bot](const std::string& m) {
			std::istringstream iss(m);
			std::string type, to, text;
			
			iss >> type;
			
			if (type == "PING") {
				text = "";
				while ((iss >> to)) {
					text += to + " ";
				}
				
				bot.pong(text);
			}
		});
		
		bot.add_read_handler([&bot](const std::string& m) {
			std::istringstream iss(m);
			std::string from, type, to, msg, text;
			
			iss >> from >> type >> to >> msg;
			
			if (msg == ":!echo") {
				text = "";
				while ((iss >> msg)) {
					text += msg + " ";
				}
				
				if (text != "") {
					bot.message(to, text);
				}
			}
		});
		
		bot.add_read_handler([&bot](const std::string& m) {
			std::istringstream iss(m);
			std::ostringstream oss;
			std::string from, type, to, msg;
			
			iss >> from >> type >> to >> msg;
			
			if (msg == ":!rand") {
				int mx, ans = std::rand();
				
				if (iss >> mx) {
					ans = ans % mx;
				}
				
				oss << ans;
				bot.message(to, from + ": " + oss.str());
			}
		});
		
		// Main execution
		bot.loop();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
