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
    this->_mutex = std::make_shared<std::mutex>();
    this->_receiverMutex = std::make_shared<std::mutex>();
    this->_packetTracker = std::make_shared<PacketTracker>();
    this->_ipPort = {ipAdress, port};
    this->_queueMsg = std::make_shared<RType::MessageSendedQueue>(importantMessagesCode);
    this->_instance = std::make_shared<SocketHandler>(*this);
    this->_threadOpen = std::make_shared<bool>(true);
    this->_senderThread = std::make_shared<std::thread>(&RType::Utils::SocketHandler::senderThread, this);
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
    this->_threadOpen = socket._threadOpen;
    this->_senderThread = socket._senderThread;

}

RType::Utils::SocketHandler::~SocketHandler()
{
    *this->_threadOpen = false;
    this->_senderThread->join();
}

auto clockReceive = std::chrono::steady_clock::now();
size_t nbMsg = 0;

RType::Utils::MessageParsed_s RType::Utils::SocketHandler::receive()
{
    unsigned long data;
    // boost::asio::mutable_buffer buffer(&data, sizeof(data));
    std::unique_lock<std::mutex> lock(*this->_receiverMutex);
    std::list<Utils::MessageParsed_s> msgNotReceived;
    boost::asio::streambuf response;
    MessageParsed_s msg;
    auto buff = response.prepare(ENCODED_MESSAGE_SIZE);
    this->_socket->receive_from(buff, _Endpoint);
    response.commit(ENCODED_MESSAGE_SIZE);
    std::istream respStream(&response);
    respStream >> msg;
    msg.senderIp = _Endpoint.address().to_v4().to_string();
    msg.senderPort = _Endpoint.port();
    // Utils::MessageParsed_s msg(data, _Endpoint.address().to_v4().to_string(), _Endpoint.port());
    auto clock = std::chrono::steady_clock::now();
    nbMsg++;
    if (std::chrono::duration_cast<std::chrono::microseconds>(clock - clockReceive).count() > 1000000) {
        std::cout << "Receive " << nbMsg << "Packets in one sec" << std::endl;
        nbMsg = 0;
        clockReceive = clock;
    }
    // if (this->_queueMsg->isImportant(msg)) {
    //     this->_packetTracker->receiveMessage(msg, msgNotReceived);
    //     while (!msgNotReceived.empty()) {
    //         auto it = msgNotReceived.front();
    //         this->_queueMsg->addMessage(it);
    //         msgNotReceived.pop_front();
    //     }
    //     Utils::MessageParsed_s toFill;
    //     if (this->_packetTracker->reSendMessage(toFill, msg)) {
    //         if (toFill.msgType == 13)
    //             std::cout << "Receive delete message.." << std::endl;
    //         return toFill;
    //     }
    //     if (msg.msgType == 34)
    //         return this->receive();
    // }
    return msg;
}

void RType::Utils::SocketHandler::send(const MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_queueMsg->addMessage(msg);
    // if (!this->_queueMsg->readyToGetMessage())
    //     return;
    // bool isImportant = false;
    // auto toSend = this->_queueMsg->getMessage(isImportant);
    // // if (isImportant)
    // //     this->_packetTracker->prepareMessageToSend(toSend);
    // unsigned long compressed = toSend.encode();
    // boost::asio::const_buffer buffer(&compressed, sizeof(compressed));
    // try {
    //     _socket->send_to(buffer, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(toSend.senderIp), toSend.senderPort));
    // } catch (const boost::system::system_error &err) {
    //     std::cerr << "Send error " << err.code() << std::endl; 
    // }
}

std::shared_ptr<RType::Utils::SocketHandler> RType::Utils::SocketHandler::getInstance() const
{
    return this->_instance;
}

const std::pair<std::string, int> &RType::Utils::SocketHandler::getIpAndPort() const
{
    return this->_ipPort;
}


auto clockSend = std::chrono::steady_clock::now();
size_t nbMsgSend = 0;

void RType::Utils::SocketHandler::send()
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    if (!this->_queueMsg->readyToGetMessage())
        return;
    bool isImportant = false;
    auto toSend = this->_queueMsg->getMessage(isImportant);
    // if (isImportant)
    //     this->_packetTracker->prepareMessageToSend(toSend);
    boost::asio::streambuf request;
    std::ostream reqStream(&request);
    reqStream << toSend;
    auto buff = request.data();
    try {
        _socket->send_to(buff, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(toSend.senderIp), toSend.senderPort));
    } catch (const boost::system::system_error &err) {
        std::cerr << "Send error " << err.code() << std::endl; 
    }
    ++nbMsgSend;
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::microseconds>(clock - clockSend).count() > 1000000) {
        std::cout << "Send " << nbMsgSend << "Packets in one sec" << std::endl;
        nbMsgSend = 0;
        clockSend = clock;
    }
}

void RType::Utils::SocketHandler::senderThread()
{
    while (this->_threadOpen) {
        std::this_thread::sleep_for(std::chrono::microseconds(this->_queueMsg->getMessageDelay() / 2));
        if (!this->_queueMsg->empty())
            this->send();
    }
}