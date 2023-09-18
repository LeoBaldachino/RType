/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** CoreServer
*/

#include "includes/CoreServer.hpp"

RType::CoreServer::CoreServer(int ar, char **av)
{
    if (ar < 2)
        throw std::invalid_argument("Not enougth arguments");
    this->_socket = std::make_unique<Utils::SocketServer>(std::atoi(av[1]));
    this->run();
}

RType::CoreServer::~CoreServer()
{

}

void RType::CoreServer::run()
{
    this->_socket->receive(-1);
}
