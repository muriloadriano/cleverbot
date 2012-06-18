#include "logger.h"
#include "connection.h"
#include <stdexcept>
#include <thread>

namespace clever_bot {

void connection::connect() 
{
	boost::asio::ip::tcp::resolver resolver(m_io_service);
	boost::asio::ip::tcp::resolver::query query(m_addr, m_port);
	boost::system::error_code error = boost::asio::error::host_not_found;
	
	auto iter = resolver.resolve(query);
	decltype(iter) end;
	
	while (iter != end) {
		if (!error) {
			break;
		}
		
		m_socket.close();
		LOG("Info", "Trying to connect: " + m_addr + ":" + m_port);
		
		m_socket.connect(*iter++, error);
		
		if (error) {
			LOG("ERROR", error.message());
		}
	}
	
	if (error) {
		throw std::runtime_error(error.message());
	}
	
	LOG("Info", "Connected!");
}

void connection::run()
{
	m_io_service.run();
	std::thread write_handler_thread(m_write_handler);
	write_handler_thread.join();
}

void connection::connect(const std::string& addr, const std::string& port)
{
	m_addr = addr;
	m_port = port;
	
	connect();
}

void connection::write(const std::string& content)
{
	LOG("Write", content);
	boost::asio::write(m_socket, boost::asio::buffer(content + "\r\n"));
}

void connection::set_read_handler(const read_handler_type& handler)
{
	m_read_handler = handler;
}

void connection::set_write_handler(const write_handler_type& handler)
{
	m_write_handler = handler;
}

} // ns clever_bot