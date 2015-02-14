all:
	g++ -std=c++11 -Wall *.cpp -lboost_system -lpthread -o bot

debug:
	g++-mp-4.7 -std=c++11 -Wall main.cpp connection.cpp bot.cpp logger.cpp -o bot -lboost_system -ggdb

clean:
	rm bot
