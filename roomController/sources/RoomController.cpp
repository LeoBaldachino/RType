/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomController
*/

#include "../includes/RoomController.hpp"

RType::RoomController::RoomController(int ac, char **av) :
_lineCommands({{"ls", &RType::RoomController::lsCommand}})
{
    if (ac != 3)
        throw std::invalid_argument("Not enougth arguments");
    this->_serverIp = av[1];
    this->_serverPort = std::stoi(std::string(av[2]));
    this->_threadOpen = true;
    this->_socket = std::make_unique<Utils::SocketHandler>("127.0.0.1", 4001 + std::rand() % 3000, std::list<int>({keyPressed, entityType, playerPing, newPlayerConnected, givePlayerId, destroyedRoom, serverStop, entityType, removeEntity, playerDeconnected, newRoomIsCreated, playerGetId, givePlayerId}));
    this->_commandsThread = std::make_unique<std::thread>(&RType::RoomController::launchGetter, this);
    this->run();
}

RType::RoomController::~RoomController()
{
    this->_threadOpen = false;
    this->_commandsThread->join();
}

void RType::RoomController::launchGetter()
{
    while (this->_threadOpen) {
        auto msg = this->_socket->receive();
        auto it = this->_commands.find(msg.msgType);
        if (it == this->_commands.end()) {
            std::cout << "Get an unhandled message " << static_cast<int>(msg.msgType) << std::endl;
            continue;
        }
        (this->*it->second)(msg);
    }
}

void RType::RoomController::run()
{
    while (true) {
        std::string actual_line;
        std::cout << "> ";
        if (!std::getline(std::cin, actual_line, '\n'))
            return;
        auto it = this->_lineCommands.find(actual_line);
        if (it == this->_lineCommands.end()) {
            std::cout << "Don't know the command '" << actual_line << "' try help" << std::endl;
            continue;
        }
        (this->*it->second)(actual_line);
    }
}

void RType::RoomController::lsCommand(const std::string &command)
{
    (void)command;
    std::cout << "This is ls command !" << std::endl;
}