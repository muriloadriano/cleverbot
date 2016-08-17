#ifndef CLEVERBOT_CONNECTION_H
#define CLEVERBOT_CONNECTION_H

#include <string>
#include <functional>
#include <boost/asio.hpp>

namespace clever_bot {

typedef std::function<void (const std::string&)> read_handler_type;
typedef std::function<void (void)> write_handler_type;

class connection
{	
public:
	connection() : m_socket(m_io_service) {}
	
	connection(const std::string& addr, const std::string& port) 
		: m_addr(addr), m_port(port), m_socket(m_io_service)
	{
		connect();	
	}
	
	void connect();
	void connect(const std::string& addr, const std::string& port);
	void write(const std::string& content);
	void read(const boost::system::error_code& error, std::size_t);
	
	void set_read_handler(const read_handler_type& handler);
	void set_write_handler(const write_handler_type& handler);
	
	void run();
	void close();
	bool alive() const;
	
private:
	std::string m_addr;
	std::string m_port;
	
	boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::socket m_socket;
	
	read_handler_type m_read_handler;
	write_handler_type m_write_handler;
	
	std::array<char, 256> m_buffer;
};

} // ns clever_bot

#endif