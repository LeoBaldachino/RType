/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Room
*/

#include "../includes/Room.hpp"

RType::Server::Room::Room(unsigned char id, unsigned char maxSize, std::shared_ptr<Utils::SocketHandler> setSocket, std::vector<std::map<Parser::Enemies, int>> waves) : _socket(setSocket)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_willBeDestroyed = false;
    this->_id = id;
    this->_maxSize = maxSize;
    this->_isOpen = true;
    this->_actualPing = 0;
    this->_firstClient = {"", -1};
    this->_pingTime = std::chrono::steady_clock::now();
    this->_mutexQueue = std::make_unique<std::mutex>();
    this->_toSendToGameLoop = std::make_unique<std::queue<std::pair<unsigned short, Utils::MessageParsed_s>>>();
    this->_gameLoop = std::make_unique<RTypeGameLoop>(this->_core);
    this->setEnemiesWaves(waves);
    this->_roomThread = std::make_unique<std::thread>(&RType::Server::Room::runRoom, this);
}

RType::Server::Room::~Room()
{
    this->stopRoom();
    this->_roomThread->join();
}


bool RType::Server::Room::addToRoom(const std::pair<std::string, int> &newPlayer)
{
    if (this->_willBeDestroyed || this->_allPlayers.size() >= this->_maxSize)
        return false;
    auto it = this->_allPlayers.begin();
    for (; it != this->_allPlayers.end(); it++)
        if (it->first == newPlayer)
            return false;
    Utils::MessageParsed_s msg;
    unsigned short newId;
    {
        std::unique_lock<std::mutex> lock(this->_mutex);
        msg.msgType = newPlayerConnected;
        msg.senderIp = newPlayer.first;
        msg.senderPort = newPlayer.second;
        if (this->_firstClient.first == "" && this->_firstClient.second == -1)
            this->_firstClient = newPlayer;
        newId = this->_core.getAvailabeIndex();
        this->_core.addEntity(std::make_shared<Player>(Position(0, 0, 1920, 1080)), newId);
        for (auto &it : this->_allPlayers) {
            msg.msgType = newPlayerConnected;
            msg.setFirstShort(it.second);
            this->_socket->send(msg);
            msg.msgType = moveAnEntity;
            auto coreIt = this->_core._entities.find(it.second);
            if (coreIt == this->_core._entities.end())
                continue;
            msg.setThirdShort(it.second);
            msg.setSecondShort(coreIt->second->getPosition().getY());
            msg.setFirstShort(coreIt->second->getPosition().getX());
            this->_socket->send(msg);
        }
        msg.setFirstShort(newId);
        lock.unlock();
        this->notifyAllPlayer(msg);
        lock.lock();
        this->_allPlayers.insert({newPlayer, newId});
        this->_playerOnline.insert({newPlayer, true});
        msg.msgType = givePlayerId;
        msg.setFirstShort(newId);
        msg.senderIp = newPlayer.first;
        msg.senderPort = newPlayer.second;
        this->_socket->send(msg);
    }
    std::unique_lock<std::mutex> lock(*this->_mutexQueue);
    msg.msgType = newPlayerConnected;
    this->_toSendToGameLoop->push({newId, msg});
    return true;
}

unsigned char RType::Server::Room::getId() const
{
    return this->_id;
}

bool RType::Server::Room::isInRoom(const std::pair<std::string, int> &toSearch) const
{
    if (this->_willBeDestroyed)
        return false;
    auto it = this->_allPlayers.begin();
    for (; it != this->_allPlayers.end(); it++)
        if (it->first == toSearch)
            return true;
    return false;
}

bool RType::Server::Room::sendMessageToRoom(const Utils::MessageParsed_s &msg)
{
    if (this->_willBeDestroyed)
        return false;
    this->messagePing(msg);
    if (msg.msgType == playerGetId) {
        this->sendPlayerId(msg);
        return true;
    }
    if (msg.msgType == entityType) {
        this->sendEntityType(msg);
        return true;
    }
    auto it = this->_allPlayers.find({msg.senderIp, msg.senderPort});
    if (it == this->_allPlayers.end())
        return false;
    std::unique_lock<std::mutex> lock(*this->_mutexQueue);
    this->_toSendToGameLoop->push({it->second, msg});
    return true;
}

bool RType::Server::Room::isFull() const 
{
    return (this->_allPlayers.size() >= this->_maxSize);
}

void RType::Server::Room::stopRoom()
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_isOpen = false;
}

void RType::Server::Room::runRoom()
{
    int nbMsg = DESTROYED_NB_MSG_SEND;
    while (this->_isOpen) {
        if (_willBeDestroyed) {
            std::unique_lock<std::mutex> lock(this->_mutex);
            Utils::MessageParsed_s msg;
            msg.msgType = destroyedRoom;
            for (const auto &it : this->_allPlayers) {
                msg.senderIp = it.first.first;
                msg.senderPort = it.first.second;
                for (int i = 0; i < nbMsg; ++i)
                    this->_socket->send(msg);
            }
            return;
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - this->_pingTime).count() >= static_cast<int>(CHECK_CRASHED_SECONDS)) {
            this->checkCrashed();
            this->_pingTime = std::chrono::steady_clock::now();
        }
        std::unique_lock<std::mutex> lock(*this->_mutexQueue);
        auto ret = this->_gameLoop->updateGameLoop(*this->_toSendToGameLoop);
        this->_toSendToGameLoop = std::make_unique<std::queue<std::pair<unsigned short, Utils::MessageParsed_s>>>();
        while (!ret.empty()) {
            this->notifyAllPlayer(ret.front());
            ret.pop();
        }
    }
}

bool RType::Server::Room::removeFromRoom(const Utils::MessageParsed_s &toRm)
{
    std::pair<std::string, int> toRemove(toRm.senderIp, toRm.senderPort);
    bool isFirst = false;
    if (this->_willBeDestroyed)
        return false;
    for (auto it = this->_allPlayers.begin(); it != this->_allPlayers.end(); it++) {
        if (it->first == toRemove) {
            this->_core.removeEntity(it->second);
            if (it->first == this->_firstClient) {
                isFirst = true;
                std::unique_lock<std::mutex> lock(this->_mutex);
                _willBeDestroyed = true;
            }
            {
                std::unique_lock<std::mutex> lock(*this->_mutexQueue);
                Utils::MessageParsed_s newMsg(toRm);
                newMsg.msgType = playerDeconnected;
                this->_toSendToGameLoop->push({it->second, newMsg});
                this->notifyAllPlayer(newMsg);
            }
            this->_allPlayers.erase(it);
            return isFirst;
        } 
    }
    return false;
}

bool RType::Server::Room::willBeDestroyed() const
{
    return this->_willBeDestroyed;
}

void RType::Server::Room::waitForDestroy()
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    return;
}

int RType::Server::Room::getMaxPlayers() const
{
    return this->_maxSize;
}

int RType::Server::Room::getNumberOfPlayer() const
{
    return this->_allPlayers.size();
}

void RType::Server::Room::notifyAllPlayer(const Utils::MessageParsed_s &msg)
{
    auto newMsg = msg;
    std::unique_lock<std::mutex> lock(this->_mutex);
    for (auto &it : this->_allPlayers) {
        newMsg.senderIp = it.first.first;
        newMsg.senderPort = it.first.second;
        this->_socket->send(newMsg);
    }
}

void RType::Server::Room::checkCrashed()
{
    Utils::MessageParsed_s msg;
    msg.msgType = playerPing;
    if (_actualPing < static_cast<int>(CHECK_CRASHED_TIMES)) {
        this->_actualPing++;
        return this->notifyAllPlayer(msg);
    }
    _actualPing = 0;
    std::queue<std::pair<std::pair<std::string, int>, unsigned char>> playerDisconnected;
    int cp = 0;
    for (auto &it : this->_playerOnline) {
        if (!it.second)
            playerDisconnected.push({it.first, cp});
        it.second = false;
        ++cp;
    }
    while (!playerDisconnected.empty()) {
        Utils::MessageParsed_s msg;
        msg.bytes[0] = this->_id;
        msg.bytes[1] = static_cast<unsigned char>(std::get<3>(this->_gameLoop->getPlayerDetails(playerDisconnected.front().second)));
        msg.senderPort = playerDisconnected.front().first.second;
        msg.senderIp = playerDisconnected.front().first.first;
        this->removeFromRoom(msg);
        playerDisconnected.pop();
    }
}

void RType::Server::Room::messagePing(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_playerOnline[{msg.senderIp, msg.senderPort}] = true;
    return;
}

void RType::Server::Room::setDestroy()
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_willBeDestroyed = true;
}

void RType::Server::Room::sendPlayerId(const Utils::MessageParsed_s &msg)
{
    Utils::MessageParsed_s newMsg(msg);
    newMsg.msgType = givePlayerId;
    auto it = this->_allPlayers.find({msg.senderIp, msg.senderPort});
    if (it == this->_allPlayers.end())
        return;
    newMsg.setFirstShort(it->second);
    this->_socket->send(newMsg);
}

void RType::Server::Room::sendEntityType(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    Utils::MessageParsed_s newMsg(msg);
    auto it = this->_core._entities.find(msg.getFirstShort());
    if (it == this->_core._entities.end())
        return;
    newMsg.setSecondShort(this->_gameLoop->getEntityType(msg.getFirstShort()));
    this->_socket->send(newMsg);
}

std::tuple<unsigned short, unsigned short, unsigned short, unsigned short> RType::Server::Room::getPlayerDetails(unsigned char playerId)
{
    return this->_gameLoop->getPlayerDetails(playerId);
}


bool RType::Server::Room::removeFromRoom(unsigned short id)
{
    Utils::MessageParsed_s msg;
    msg.bytes[0] = this->_id;
    msg.bytes[1] = id;
    for (auto &it : this->_allPlayers)
        if (it.second == id) {
            msg.senderIp = it.first.first;
            msg.senderPort = it.first.second;
            return this->removeFromRoom(msg);
        }
    return false;
}
void RType::Server::Room::setEnemiesWaves(std::vector<std::map<Parser::Enemies, int>> waves)
{
    this->_gameLoop->setEnemiesWaves(waves);
}
