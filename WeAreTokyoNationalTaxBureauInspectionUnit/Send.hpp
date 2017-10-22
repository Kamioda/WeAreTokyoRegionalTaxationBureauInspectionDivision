#ifndef __SEND_HPP__
#define __SEND_HPP__
#if !defined( WINVER ) || ( WINVER < 0x0601 )
#undef  WINVER
#define WINVER 0x0601
#endif
#if !defined( _WIN32_WINNT ) || ( _WIN32_WINNT < 0x0601 )
#undef  _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK
#endif
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/archive/text_oarchive.hpp>

class Send {
private:
	boost::asio::io_service IOService;
	boost::optional<boost::asio::ip::tcp::socket> Socket;
	boost::optional<boost::asio::ip::tcp::endpoint> Endpoint;
	boost::archive::text_oarchive OA;
public:
	Send(const std::string& IP, std::ostringstream& Ostr, const unsigned short PortNumber = 0);
	Send(std::ostringstream& Ostr, const unsigned short PortNumber = 0);
	template<typename T> void InputData(const T& Data) { this->OA << Data; }
	void send(const std::ostringstream& ostr);
	unsigned short PortNumber;
};
#endif
