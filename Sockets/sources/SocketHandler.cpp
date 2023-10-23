/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler
*/

#include "../includes/SocketHandler.hpp"


RType::Utils::SocketHandler::SocketHandler(const std::string &ipAdress, int port, const std::list<int> &importantMessagesCode)
{
    _socket = std::make_shared<boost::asio::ip::udp::socket>(_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
    _mutex = std::make_shared<std::mutex>();
    this->_receiverMutex = std::make_shared<std::mutex>();
    this->_packetTracker = std::make_shared<PacketTracker>();
    this->_ipPort = {ipAdress, port};
    this->_queueMsg = std::make_shared<RType::MessageSendedQueue>(importantMessagesCode);
    this->_instance = std::make_shared<SocketHandler>(*this);
}

RType::Utils::SocketHandler::SocketHandler(const SocketHandler &socket) : _socket(socket._socket)
{
    this->_Endpoint = socket._Endpoint;
    this->_instance = socket._instance;
    this->_mutex = socket._mutex;
    this->_socket = socket._socket;
    this->_receiverMutex = socket._receiverMutex;
    this->_queueMsg = socket._queueMsg;
    this->_packetTracker = socket._packetTracker;
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
    std::list<Utils::MessageParsed_s> msgNotReceived;
    _socket->receive_from(buffer, _Endpoint);
    Utils::MessageParsed_s msg(data, _Endpoint.address().to_v4().to_string(), _Endpoint.port());
    if (this->_queueMsg->isImportant(msg)) {
        this->_packetTracker->receiveMessage(msg, msgNotReceived);
        while (!msgNotReceived.empty()) {
            auto it = msgNotReceived.front();
            this->_queueMsg->addMessage(it);
            msgNotReceived.pop_front();
        }
        Utils::MessageParsed_s toFill;
        if (this->_packetTracker->reSendMessage(toFill, msg)) {
            if (toFill.msgType == 13)
                std::cout << "Receive delete message.." << std::endl;
            return toFill;
        }
        if (msg.msgType == 34)
            return this->receive();
    }
    if (msg.msgType == 13)
        std::cout << "Receive delete message.." << std::endl;
    return msg;
}

void RType::Utils::SocketHandler::send(const struct MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_queueMsg->addMessage(msg);
    if (!this->_queueMsg->readyToGetMessage())
        return;
    bool isImportant = false;
    auto toSend = this->_queueMsg->getMessage(isImportant);
    if (isImportant)
        this->_packetTracker->prepareMessageToSend(toSend);
    unsigned long long compressed = toSend.encode();
    boost::asio::const_buffer buffer(&compressed, sizeof(compressed));
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

void RType::Utils::SocketHandler::sendAllMessagesFromImportant()
{
    bool isImportant = true;
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto toSend = this->_queueMsg->getMessage(isImportant);
    while (isImportant) {
        if (isImportant)
            this->_packetTracker->prepareMessageToSend(toSend);
        unsigned long long compressed = toSend.encode();
        boost::asio::const_buffer buffer(&compressed, sizeof(compressed));
        try {
            _socket->send_to(buffer, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(toSend.senderIp), toSend.senderPort));
        } catch (const boost::system::system_error &err) {
            std::cerr << "Send error 2 " << err.code() << std::endl; 
        }
        toSend = this->_queueMsg->getMessage(isImportant);
    }   

}