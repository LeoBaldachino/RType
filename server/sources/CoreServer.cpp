/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** CoreServer
*/

#include "../includes/CoreServer.hpp"


RType::CoreServer::CoreServer(int ar, char **av)
{
    if (ar < 2)
        throw std::invalid_argument("Not enougth arguments");
    this->_threadIsOpen = true;
    this->_socket = std::make_unique<Utils::SocketHandler>(av[1], std::atoi(av[2]));
    this->_threadPool = std::make_unique<Server::ThreadPool>(std::thread::hardware_concurrency() - 1);
    this->_threadPool->InitThreadPool();
    this->_senderThread = std::make_unique<std::thread>(&RType::CoreServer::sendInfosThread, this);
    this->run();
}

RType::CoreServer::~CoreServer()
{
    this->_threadIsOpen = false;
    this->_senderThread->join();
    this->_threadPool->CloseThreadPool();
}

void RType::CoreServer::run()
{
    while (1) {
        RType::Utils::MessageParsed_s tmpMsg = this->_socket->receive();
        auto it = this->_clients.begin();
        std::pair<std::string, int> tmpPair = {tmpMsg.senderIp, tmpMsg.senderPort};
        for (; it < this->_clients.end(); it++)
            if (*it == tmpPair)
                break;
        if (it == this->_clients.end())
            _clients.push_back(tmpPair);
        this->_threadPool->AddTask([this, tmpMsg]{this->threadMethod(tmpMsg);});
    }
}

void RType::CoreServer::sendInfosThread()
{
    while (_threadIsOpen) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //notify the state of everyone
    }
}

void RType::CoreServer::threadMethod(const Utils::MessageParsed_s &msg)
{
    if (msg.msgType == move) {
        std::cout << "object " << std::endl;
        return;
    }
}