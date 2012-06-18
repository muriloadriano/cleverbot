#ifndef BOT_H
#define BOT_H

#include <map>
#include <string>
#include "connection.h"

namespace clever_bot {

class bot
{
public:
	bot(const std::string& config_file);
	void nick(const std::string& nck);
	void join(const std::string& chann, std::string key = "");
	//void part(const std::string& chann);
	//void invite(const std::string& nck, const std::string& chann);
	//void kick(const std::string& nck, const std::string& chann);
	void message(const std::string& receiver, const std::string& message);
	void quit(const std::string& message);
	void loop();

protected:
	void write_handler();
	
	std::map<std::string, std::string> m_config;
	connection m_conn;
};

} // ns clever_bot

#endif