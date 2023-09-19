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
    this->_socket = std::make_unique<Utils::SocketHandler>(std::atoi(av[1]));
    this->_threadPool = std::make_unique<Server::ThreadPool>(std::thread::hardware_concurrency() - 1);
    this->_threadPool->InitThreadPool();
    this->_senderThread = std::make_unique<std::thread>(&RType::CoreServer::sendInfosThread, this);
    this->run();
}

RType::CoreServer::~CoreServer()
{
    this->_threadPool->CloseThreadPool();
}

void RType::CoreServer::run()
{
    RType::Utils::MessageParsed_s tmpMsg = this->_socket->receive();
    this->_threadPool->AddTask([this, tmpMsg]{this->threadMethod(tmpMsg);});
}

void RType::CoreServer::sendInfosThread()
{

}