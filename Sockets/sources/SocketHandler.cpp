/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler
*/

#include "../includes/SocketHandler.hpp"


RType::Utils::SocketHandler::SocketHandler(const std::string &ipAdress, int port) : _socket{_ioService}
{
    _socket.open(boost::asio::ip::udp::v4());
    _socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ipAdress), port));
}

RType::Utils::SocketHandler::~SocketHandler()
{
    _socket.close();
}

template<typename T, typename R>
RType::Utils::MessageParsed_s<R> RType::Utils::SocketHandler::receive(T &toPass)
{
    _socket.receive_from(, _Endpoint);
}

template<typename T>
void handleReceive(const boost::system::error_code& error, size_t bytes_transferred, T &toPass)
{

}

template<typename T>
void RType::Utils::SocketHandler::send(const MessageParsed_s<T> &toSend, const std::string &ipAdress, int port)
{
    const char *sendFormatted = reinterpret_cast<const char*>(&toSend);
    boost::system::error_code err;
    _socket.send_to(boost::asio::buffer(sendFormatted), boost::asio::ip::udp::endpoint(address::from_string(ipAdress), port), 0, err);
    std::cout << "error : " << err << std::endl;
}