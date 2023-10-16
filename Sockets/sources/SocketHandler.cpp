/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler
*/

#include "../includes/SocketHandler.hpp"


RType::Utils::SocketHandler::SocketHandler(const std::string &ipAdress, int port, bool check)
{
    _socket = std::make_shared<boost::asio::ip::udp::socket>(_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    // _socket->open(boost::asio::ip::udp::v4());
    // _socket->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    _mutex = std::make_shared<std::mutex>();
    this->_receiverMutex = std::make_shared<std::mutex>();
    this->_ipPort = {ipAdress, port};
    this->_instance = std::make_shared<SocketHandler>(*this);
}

RType::Utils::SocketHandler::SocketHandler(const SocketHandler &socket) : _socket(socket._socket)
{
    this->_Endpoint = socket._Endpoint;
    this->_instance = socket._instance;
    this->_mutex = socket._mutex;
    this->_socket = socket._socket;
    this->_receiverMutex = socket._receiverMutex;
}

RType::Utils::SocketHandler::~SocketHandler()
{
    _socket->close();
}

RType::Utils::MessageParsed_s RType::Utils::SocketHandler::receive()
{
    unsigned long long data;
    boost::asio::mutable_buffer buffer(&data, sizeof(data));
    std::unique_lock<std::mutex> lock(*this->_receiverMutex);
    _socket->receive_from(buffer, _Endpoint);
    Utils::MessageParsed_s msg(data, _Endpoint.address().to_v4().to_string(), _Endpoint.port());
    return msg;
}

void RType::Utils::SocketHandler::send(const struct MessageParsed_s &toSend)
{
    unsigned long long compressed = toSend.encode();
    boost::asio::const_buffer buffer(&compressed, sizeof(compressed));
    std::unique_lock<std::mutex> lock(*this->_mutex);
    try {
        _socket->send_to(buffer, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(toSend.senderIp), toSend.senderPort));
    } catch (const boost::system::system_error &err) {
        std::cerr << "Send error " << err.code() << std::endl; 
    }
}

std::shared_ptr<RType::Utils::SocketHandler> RType::Utils::SocketHandler::getInstance() const
{
    return this->_instance;
}

const std::pair<std::string, int> &RType::Utils::SocketHandler::getIpAndPort() const
{
    return this->_ipPort;
}