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
    this->_socket = std::make_unique<Utils::SocketHandler>(av[1], std::atoi(av[2]));
    this->_threadPool = std::make_unique<Server::ThreadPool>(std::thread::hardware_concurrency() - 1);
    this->_threadPool->InitThreadPool();
    this->run();
}

RType::CoreServer::~CoreServer()
{
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

void RType::CoreServer::threadMethod(const Utils::MessageParsed_s &msg)
{
    std::cout << "message received " << msg.msgType << std::endl;
    if (msg.msgType == newPlayerConnected) {
        if (this->_rooms.empty()) {
            std::cerr << "Rooms are empty !" << std::endl;
            return;
        }
        for (auto &it : this->_rooms)
            if (it->getId() == msg.bytes[0]) {
                if (!it->addToRoom({msg.senderIp, msg.senderPort})) {
                    Utils::MessageParsed_s newMsg;
                    newMsg.msgType = illegalAction;
                    //need to set the id of the object
                    //newMsg.byte[0];newMsg.bytes[1]
                    newMsg.bytes[0] = 1;
                    newMsg.bytes[1] = 2;
                    newMsg.bytes[2] = newPlayerConnected;
                    newMsg.senderIp = msg.senderIp;
                    newMsg.senderPort = msg.senderPort;
                    std::cerr << "Cannot add the player to the team" << std::endl;
                    this->_socket->send(newMsg);
                };
                return;
            }
    }
    if (msg.msgType == newRoomIsCreated)
        return this->newRoomCreated(msg);
    if (msg.msgType == getListOfRooms)
        return this->getRoomList(msg);
    if (msg.msgType == playerDeconnected)
        return this->getOutFromRoom(msg);
    for (auto &it : this->_rooms)
        if (it->isInRoom({msg.senderIp, msg.senderPort})) {
            it->sendMessageToRoom(msg);
            return;
        }
    std::cerr << "This user is in no rooms" << std::endl;
}

void RType::CoreServer::newRoomCreated(const Utils::MessageParsed_s &msg)
{
    for (auto & it : this->_rooms)
        if (it->getId() == msg.bytes[0]) {
            Utils::MessageParsed_s newMsg;
            newMsg.msgType = illegalAction;
            //need to set the id of the object
            //newMsg.byte[0];newMsg.bytes[1]
            newMsg.bytes[0] = 1;
            newMsg.bytes[1] = 2;
            newMsg.bytes[2] = newRoomIsCreated;
            newMsg.senderIp = msg.senderIp;
            newMsg.senderPort = msg.senderPort;
            std::cerr << "team aldready exist" << std::endl;
            this->_socket->send(newMsg);
            return;
        }
    std::cerr << "Team " << static_cast<int>(msg.bytes[0]) << " is created !" << std::endl;
    this->_rooms.push_back(std::make_unique<Server::Room>(msg.bytes[0], ROOM_MAX_SIZE, this->_socket->getInstance()));
    this->_rooms.back()->addToRoom({msg.senderIp, msg.senderPort});
    return;
}

void RType::CoreServer::getOutFromRoom(const Utils::MessageParsed_s &msg)
{
    for (auto it = this->_rooms.begin(); it < this->_rooms.end(); it++) {
        if ((*it)->getId() == msg.bytes[0])
            if (!(*it)->removeFromRoom({msg.senderIp, msg.senderPort}) && (*it)->willBeDestroyed()) {
                (*it)->waitForDestroy();
                std::unique_lock<std::mutex>(this->_mutex);
                std::cout << "Remove room with id " << (*it)->getId() << std::endl;
                this->_rooms.erase(it);
                return;
            }
    }
    std::cout << "No rooms with this id" << std::endl;
    Utils::MessageParsed_s newMsg;
    newMsg.msgType = illegalAction;
    //need to set the id of the object
    //newMsg.byte[0];newMsg.bytes[1]
    newMsg.bytes[0] = 1;
    newMsg.bytes[1] = 2;
    newMsg.bytes[2] = playerDeconnected;
    newMsg.senderIp = msg.senderIp;
    newMsg.senderPort = msg.senderPort;
    this->_socket->send(newMsg);
    return;
}

void RType::CoreServer::getRoomList(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg = msg;
    newMsg.msgType = listOfRooms;
    for (auto &it : this->_rooms) {
        newMsg.bytes[0] = it->getId();
        newMsg.bytes[1] = it->getNumberOfPlayer();
        newMsg.bytes[2] = it->getMaxPlayers();
        this->_socket->send(newMsg);
    }
}