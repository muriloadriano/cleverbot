#include "bot.h"
#include <iostream>

using namespace std;

int main()
{
	try {
		clever_bot::bot bot("config");
		bot.nick("botche");
		bot.join("#murilo");
		bot.loop();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}