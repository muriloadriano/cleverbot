#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "logger.h"
#include "connection.h"
#include "bot.h"

namespace clever_bot {

	bot::bot(const std::string& config_file)
	{
		std::ifstream file(config_file);
		std::string key, value;
	
		while (file >> key >> value) {
			m_config[key] = value;
		}
	
		m_conn.set_write_handler([this]() { this->write_handler(); });
		m_conn.set_read_handler([this](const std::string& m) { 
			this->read_handler(m);
		});
	
		m_conn.connect(m_config["SERVER_ADDR"], m_config["SERVER_PORT"]);
	
		if (m_config.find("BOT_NICK") != m_config.end()) {
			nick(m_config["BOT_NICK"]);
		}
	
		if (m_config.find("CHAN_LIST") != m_config.end()) {
			join(m_config["CHAN_LIST"]);
		}
	}

	bot::bot(const std::string& server, const std::string& port)
	{
		m_conn.set_write_handler([this]() { this->write_handler(); });
		m_conn.set_read_handler([this](const std::string& m) { 
			this->read_handler(m);
		});
		m_conn.connect(server, port);	
	}

	void bot::write_handler()
	{
		std::string line, comm;
	
		while (m_conn.alive()) {
			std::getline(std::cin, line);
			std::istringstream iss(line);
		
			iss >> comm;
		
			if (comm == "/n") {
				iss >> comm;
				nick(comm);
			}
			else if (comm == "/j") {
				iss >> comm;
				join(comm);
			}
			else if (comm == "/m") {
				iss >> comm;
				message(comm, iss.str());
			}
			else if (comm == "/q") {
				iss >> comm;
				quit(comm);
			}
		}
	}

	void bot::read_handler(const std::string& message)
	{
		for (auto func: m_read_handlers) {
			func(message);
		}
	}

	void bot::add_read_handler(std::function<void (const std::string&)> func)
	{
		m_read_handlers.push_back(func);
	}

	void bot::loop()
	{
		m_conn.run();
	}

	void bot::nick(const std::string& nck)
	{
		m_conn.write(std::string("NICK ") + nck);
		m_conn.write(std::string("USER ") + nck + " * * :" + nck);
	}

	void bot::join(const std::string& chann, std::string key)
	{
		m_conn.write(std::string("JOIN ") + chann + " " + key);
	}

	void bot::message(const std::string& receiver, const std::string& message)
	{
		m_conn.write(std::string("PRIVMSG ") + receiver + " :" + message);
	}

	void bot::quit(const std::string& message)
	{
		m_conn.write(std::string("QUIT :") + message);
		m_conn.close();
	}

} // ns clever_bot
