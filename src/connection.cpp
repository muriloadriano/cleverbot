#include <stdexcept>
#include <thread>
#include <functional>
#include <string>
#include <boost/bind.hpp>
#include "logger.h"
#include "connection.h"

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
		std::thread write_handler_thread(m_write_handler);
	
		m_socket.async_read_some(boost::asio::buffer(m_buffer), 
			boost::bind(&connection::read, this,
				boost::asio::placeholders::error, 
				boost::asio::placeholders::bytes_transferred
			)
		);
	
		m_io_service.run();
		write_handler_thread.join();
	}

	bool connection::alive() const
	{
		return m_socket.is_open();
	}

	void connection::close()
	{
		m_socket.close();
		m_io_service.stop();
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

	void connection::read(const boost::system::error_code& error, std::size_t count)
	{
		if (error) {
			close();
		}
		else {
			if(std::string(m_buffer.data()).substr(0,4).compare("PING")==0) {
				m_buffer[1] = 'O';
				boost::asio::write(m_socket, boost::asio::buffer(std::string(m_buffer.data())));
			}
			
			m_read_handler(std::string(m_buffer.data(), count));
		
			m_socket.async_read_some(boost::asio::buffer(m_buffer), 
				boost::bind(&connection::read, this,
					boost::asio::placeholders::error, 
					boost::asio::placeholders::bytes_transferred
				)
			);
		}
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
