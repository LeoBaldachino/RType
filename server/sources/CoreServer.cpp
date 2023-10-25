/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** CoreServer
*/

#include "../includes/CoreServer.hpp"

bool runServer = true;
std::pair<std::string, int> ipPortServer = {};

void SigIntHandler(int signal_num)
{
    RType::Utils::SocketHandler socket(ipPortServer.first, ipPortServer.second + 1, std::list<int>({}));
    RType::Utils::MessageParsed_s msg;
    msg.msgType = RType::serverStop;
    msg.senderIp = ipPortServer.first;
    msg.senderPort = ipPortServer.second;
    socket.send(msg);
    runServer = false;
    return;
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
    this->_socket = std::make_unique<Utils::SocketHandler>((std::string("127.0.0.1")), port, std::list<int>({removeEntity, entityType, destroyedRoom, playerDeconnected}));
    Parser parser(av[2]);
    this->_music = parser.getMusic();
    this->_waves = parser.getWaves();
    this->_nextLevel = parser.getNextLevel();
    this->_parallaxIndex = parser.getParallax();
    this->_threadPool = std::make_unique<Server::ThreadPool>(std::thread::hardware_concurrency() - 1);
    ipPortServer = this->_socket->getIpAndPort();
    this->_threadPool->InitThreadPool();
    std::signal(SIGINT, SigIntHandler);
    this->run();
}

RType::CoreServer::~CoreServer()
{
    if (static_cast<bool>(this->_threadPool))
        this->_threadPool->CloseThreadPool();
}

void RType::CoreServer::run()
{
    while (runServer) {
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
    if (msg.msgType == newPlayerConnected)
        return this->connectToRoom(msg);
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
    std::unique_lock<std::mutex> lock(this->_mutex);
    std::cerr << "This user is in no rooms" << std::endl;
}

void RType::CoreServer::newRoomCreated(const Utils::MessageParsed_s &msg)
{
    for (auto & it : this->_rooms)
        if (it->getId() == msg.bytes[0] || it->isInRoom({msg.senderIp, msg.senderPort})) {
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

void RType::CoreServer::connectToRoom(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg;
    newMsg.msgType = illegalAction;
    //need to set the id of the object
    //newMsg.byte[0];newMsg.bytes[1]
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