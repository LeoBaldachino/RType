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
    this->_instance = std::make_unique<SocketHandler>(this);
}

RType::Utils::SocketHandler::~SocketHandler()
{
    _socket.close();
}

unsigned long long compressFromMessage(RType::Utils::MessageParsed_s msg) 
{
    unsigned long long newMsg = 0;
    return 
       static_cast<unsigned long long>(msg.bytes[6]) << 56 |
       static_cast<unsigned long long>(msg.bytes[5]) << 48 |
       static_cast<unsigned long long>(msg.bytes[4]) << 40 |
       static_cast<unsigned long long>(msg.bytes[3]) << 32 |
       static_cast<unsigned long long>(msg.bytes[2]) << 24 |
       static_cast<unsigned long long>(msg.bytes[1]) << 16 |
       static_cast<unsigned long long>(msg.bytes[0]) << 8  |
       static_cast<unsigned long long>(msg.msgType);
}

RType::Utils::MessageParsed_s decompressFromMessage(unsigned long long toParse)
{
    RType::Utils::MessageParsed_s msg;
    msg.msgType = (toParse & 0x0000000000000ff);
    msg.bytes[0] = (toParse & 0x0000000000ff00) >> 8;
    msg.bytes[1] = (toParse & 0x00000000ff0000) >> 16;
    msg.bytes[2] = (toParse & 0x000000ff000000) >> 24;
    msg.bytes[3] = (toParse & 0x0000ff00000000) >> 32;
    msg.bytes[4] = (toParse & 0x00ff0000000000) >> 40;
    msg.bytes[5] = (toParse & 0xff000000000000) >> 48;
    msg.bytes[6] = (toParse & 0xff00000000000000) >> 56;
    return msg;
}

RType::Utils::MessageParsed_s RType::Utils::SocketHandler::receive()
{
    unsigned long long data;
    boost::asio::mutable_buffer buffer(&data, sizeof(data));
    _socket.receive_from(buffer, _Endpoint);
    Utils::MessageParsed_s msg = decompressFromMessage(data);
    msg.senderIp = _Endpoint.address().to_v4().to_string();
    msg.senderPort = _Endpoint.port();
    return msg;
}

void RType::Utils::SocketHandler::send(const struct MessageParsed_s &toSend)
{
    unsigned long long compressed = compressFromMessage(toSend);
    boost::asio::const_buffer buffer(&compressed, sizeof(compressed));
    _socket.send_to(buffer, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(toSend.senderIp), toSend.senderPort));
}

const std::unique_ptr<RType::Utils::SocketHandler> &RType::Utils::SocketHandler::getInstance() const
{
    return this->_instance;
}