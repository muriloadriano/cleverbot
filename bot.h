#ifndef BOT_H
#define BOT_H

#include <map>
#include <string>
#include <functional>
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
	//void op(const std::string& nck, const std::string& chann);
	void pong(const std::string& to);
	void message(const std::string& receiver, const std::string& message);
	void quit(const std::string& message);
	void loop();
	
	void add_read_handler(std::function<void (const std::string&)>);
protected:
	void write_handler();
	void read_handler(const std::string& message);
	
	std::vector<std::function<void (const std::string&)>> m_read_handlers;
	std::map<std::string, std::string> m_config;
	connection m_conn;
};

} // ns clever_bot

#endif
