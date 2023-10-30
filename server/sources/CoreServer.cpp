/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** CoreServer
*/

#include "../includes/CoreServer.hpp"


void SigIntHandler(int signal_num)
{
    exit(0);
}

RType::CoreServer::CoreServer(int ar, char **av)
{
    if (ar == 2) {
        std::string arg(av[1]);
        if (arg == "-h" || arg == "--h" || arg == "--help" || arg == "-help") {
            std::cout << "R-Type Server\nUSAGE :\n ./r-type_server IP PORT" << std::endl;
            return;
        }
        throw std::invalid_argument("Invalid argument");
    }
    if (ar < 3)
        throw std::invalid_argument("Not enough arguments");
    int port = std::atoi(av[1]);
    if (port < 100)
        throw std::invalid_argument("Port is not valid");
    this->_socket = std::make_unique<Utils::SocketHandler>((std::string("127.0.0.1")), port, std::list<int>({entityType, playerPing, newPlayerConnected, givePlayerId, destroyedRoom, serverStop, entityType, removeEntity, playerDeconnected, newRoomIsCreated, playerGetId, givePlayerId}));
    Parser parser(av[2]);
    this->_music = parser.getMusic();
    this->_waves = parser.getWaves();
    this->_nextLevel = parser.getNextLevel();
    this->_parallaxIndex = parser.getParallax();
    this->_threadPool = std::make_unique<Server::ThreadPool>(std::thread::hardware_concurrency() - 1);
    this->_threadPool->InitThreadPool();
    #ifdef __unix__
        std::signal(SIGINT, SigIntHandler);
    #endif
    this->run();
}

RType::CoreServer::~CoreServer()
{
    if (static_cast<bool>(this->_threadPool))
        this->_threadPool->CloseThreadPool();
}

void RType::CoreServer::run()
{
    while (1) {
        RType::Utils::MessageParsed_s tmpMsg = this->_socket->receive();
        if (tmpMsg.msgType == cannotRead)
            continue;
        if (tmpMsg.msgType == serverStop)
            break;
        std::unique_lock<std::mutex> lock(this->_mutex);
        this->_threadPool->AddTask([this, tmpMsg]{this->threadMethod(tmpMsg);});
    }
    Utils::MessageParsed_s stopMsg;
    stopMsg.msgType = serverStop;
    for (auto &it : this->_rooms) {
        for (int i = 0; i < 5; ++i)
            it->notifyAllPlayer(stopMsg);
        std::unique_lock<std::mutex> lock(this->_mutex);
        it->setDestroy();
    }
    for (auto &it : this->_rooms)
        it->waitForDestroy();
}

void RType::CoreServer::threadMethod(const Utils::MessageParsed_s &msg)
{
    switch (msg.msgType)
    {
        case newPlayerConnected:
            return this->connectToRoom(msg);
        case newRoomIsCreated :
            return this->newRoomCreated(msg);
        case getListOfRooms :
            return this->getRoomList(msg);
        case playerDeconnected :
            return this->getOutFromRoom(msg);
        case RType::getRoomMembers :
            return this->getRoomMembers(msg);
        case RType::getPlayerInfos :
            return this->getPlayerDetails(msg);
        case RType::kickPlayer :
            return this->kickPlayer(msg);
    }
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
        if (it->getId() == msg.bytes[0] || it->isInRoom({msg.senderIp, msg.senderPort})) {
            Utils::MessageParsed_s newMsg;
            newMsg.msgType = illegalAction;
            newMsg.bytes[0] = 1;
            newMsg.bytes[1] = 2;
            newMsg.bytes[2] = newRoomIsCreated;
            newMsg.senderIp = msg.senderIp;
            newMsg.senderPort = msg.senderPort;
            std::cerr << "team aldready exist" << std::endl;
            this->_socket->send(newMsg);
            return;
        }
    std::unique_lock<std::mutex> lock(this->_mutex);
    std::cerr << "Team " << static_cast<int>(msg.bytes[0]) << " is created !" << std::endl;
    this->_rooms.push_back(std::make_unique<Server::Room>(msg.bytes[0], Server::ROOM_MAX_SIZE, this->_socket->getInstance(), this->_waves));
    this->_rooms.back()->addToRoom({msg.senderIp, msg.senderPort});
    return;
}

void RType::CoreServer::getOutFromRoom(const Utils::MessageParsed_s &msg)
{
    for (auto it = this->_rooms.begin(); it < this->_rooms.end(); it++) {
        if ((*it)->getId() == msg.bytes[0])
            if ((*it)->removeFromRoom({msg.senderIp, msg.senderPort}) && (*it)->willBeDestroyed()) {
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
    std::cout << "Get room list..." << std::endl;
    Utils::MessageParsed_s newMsg = msg;
    newMsg.msgType = listOfRooms;
    for (auto &it : this->_rooms) {
        newMsg.bytes[0] = it->getId();
        newMsg.bytes[1] = it->getNumberOfPlayer();
        newMsg.bytes[2] = it->getMaxPlayers();
        this->_socket->send(newMsg);
    }
}

void RType::CoreServer::connectToRoom(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg;
    newMsg.msgType = illegalAction;
    newMsg.bytes[0] = 1;
    newMsg.bytes[1] = 2;
    newMsg.bytes[2] = newPlayerConnected;
    newMsg.senderIp = msg.senderIp;
    newMsg.senderPort = msg.senderPort;
    if (this->_rooms.empty()) {
        std::cerr << "Rooms are empty !" << std::endl;
        return;
    }
    for (auto &it : this->_rooms)
        if (it->isInRoom({msg.senderIp, msg.senderPort})) {
            std::cout << "this player is already on a team" << std::endl;
            return this->_socket->send(newMsg);
        }
    for (auto &it : this->_rooms)
        if (it->getId() == msg.bytes[0]) {
            if (!it->addToRoom({msg.senderIp, msg.senderPort})) {
                std::cerr << "Cannot add the player to the team" << std::endl;
                this->_socket->send(newMsg);
            };
            return;
        }
}


void RType::CoreServer::getRoomMembers(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg(msg);
    for (auto &it : this->_rooms)
        if (it->getId() == msg.getFirstShort()) {
            newMsg.msgType = sendRoomMembers;
            unsigned char size = it->getNumberOfPlayer();
            for (int i = 0; i < size; ++i)
                newMsg.bytes[i] = i;
            newMsg.bytes[size] = 255;
            return this->_socket->send(newMsg);
        }
    newMsg.msgType = illegalAction;
    newMsg.bytes[3] = RType::getRoomMembers;
    return this->_socket->send(newMsg);
}

void RType::CoreServer::getPlayerDetails(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg(msg);
    for (auto &it : this->_rooms)
        if (it->getId() == msg.getFirstShort()) {
            newMsg.msgType = playerDetails;
            auto details = it->getPlayerDetails(msg.bytes[3]);
            newMsg.setFirstShort(std::get<0>(details));
            newMsg.setSecondShort(std::get<1>(details));
            newMsg.setThirdShort(std::get<2>(details));
            return this->_socket->send(newMsg);
        }
    newMsg.msgType = illegalAction;
    newMsg.bytes[3] = RType::getPlayerInfos;
    return this->_socket->send(newMsg); 
}

void RType::CoreServer::kickPlayer(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg(msg);
    for (auto &it : this->_rooms)
        if (it->getId() == msg.getFirstShort()) {
            if (!it->removeFromRoom(msg.bytes[3]))
                break;
            return;
        }
    newMsg.msgType = illegalAction;
    newMsg.bytes[3] = RType::kickPlayer;
    return this->_socket->send(newMsg); 
}