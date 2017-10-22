#include "Send.hpp"

Send::Send(const std::string& IP, std::ostringstream& ostr, const unsigned short PortNumber) 
	: OA(ostr) {
	this->Socket = boost::asio::ip::tcp::socket(this->IOService);
	this->Endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(IP), PortNumber);
	this->PortNumber = this->Endpoint->port();
}

Send::Send(std::ostringstream& ostr, const unsigned short PortNumber)
	: Send("127.0.0.1", ostr, PortNumber) {}

void Send::send(const std::ostringstream& ostr) {
	std::string Buffer = ostr.str();
	this->Socket->connect(*this->Endpoint);
	this->Socket->send(boost::asio::buffer(Buffer.data(), Buffer.size()));
}
