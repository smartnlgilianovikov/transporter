#include "session.h"
#include "file/file.h"
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

Session::Session( boost::asio::ip::tcp::socket socket):
	socket_( std::move( socket))
{
	std::cout << "Session::Session" << std::endl;
}

void Session::start()
{
	std::cout << "Session::start" << std::endl;
	read_();
}

/*
void Session::read_()
{
	auto self( shared_from_this());
	socket_.async_read_some( boost::asio::buffer( data_, maxLength),
							 [this, self]( boost::system::error_code ec, std::size_t length)
							 {
								if( !ec)
								{
									write_( length);
								}

							 });
}

void Session::write_( std::size_t length)
{
	auto self( shared_from_this());
	boost::asio::async_write( socket_,
							  boost::asio::buffer( data_, length),
							  [this, self]( boost::system::error_code ec, std::size_t length)
							  {
								 if( !ec)
								 {
									 read_();
								 }
							  });
}
*/
void Session::read_()
{
	std::cout << "Session::read_" << std::endl;
	 const std::size_t header_length = 8;
	 char inbound_header_[header_length];
	 std::cout << "before read header" << std::endl;
	 boost::asio::read( socket_, boost::asio::buffer(inbound_header_));
	 std::cout << "after read header" << std::endl;

	 // Determine the length of the serialized data.
	std::istringstream is(std::string(inbound_header_, header_length));
	std::size_t inbound_data_size = 0;
	if (!(is >> std::hex >> inbound_data_size))
	{
		 std::cout << "error" << std::endl;
		 return;
	}

	// Start an asynchronous call to receive the data.
	std::vector<char> inbound_data_;
	inbound_data_.resize(inbound_data_size);
	std::cout << "before read data" << std::endl;
	boost::asio::read( socket_, boost::asio::buffer(inbound_data_));
	std::cout << "after read header" << std::endl;

	std::string archive_data(&inbound_data_[0], inbound_data_.size());
	std::istringstream archive_stream(archive_data);
	boost::archive::text_iarchive archive(archive_stream);
	File file;
	archive >> file;

	std::cout << file << std::endl;
}
