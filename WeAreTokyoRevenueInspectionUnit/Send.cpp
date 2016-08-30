#include<boost/asio.hpp>
#include<boost/serialization/serialization.hpp>
#include<boost/archive/binary_oarchive.hpp>

template<typename T> void reserve_ip_connect(const T& data, std::string ip, int port = 0) {
	std::ostringstream ostr;
	boost::archive::binary_oarchive oa(ostr);
	oa << data;
	//ソケット接続
	boost::asio::io_service ios;
	boost::asio::ip::tcp::socket socket(ios);
	boost::system::error_code error;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
	endpoint.port();
	socket.connect(endpoint);
	std::string buf = ostr.str();
	//送信
	socket.send(boost::asio::buffer(buf.data(), buf.size()));
}

void reserve_ip_send(const std::string& str, std::string) {

}