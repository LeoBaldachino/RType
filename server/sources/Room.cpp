/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Room
*/

#include "../includes/Room.hpp"

RType::Server::Room::Room(unsigned char id, unsigned char maxSize, std::shared_ptr<Utils::SocketHandler>  setSocket) : _socket(setSocket)
{
    this->_willBeDestroyed = false;
    this->_id = id;
    this->_maxSize = maxSize;
    this->_isOpen = true;
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
    for (; it < this->_allPlayers.end(); it++)
        if (*it == newPlayer)
            return false;
    std::unique_lock<std::mutex> lock(this->_mutex);
    std::cout << "add client to room " << newPlayer.second << std::endl;
    this->_allPlayers.push_back(newPlayer);
    return true;
}

int RType::Server::Room::getId() const
{
    return this->_id;
}

bool RType::Server::Room::isInRoom(const std::pair<std::string, int> &toSearch) const
{
    if (this->_willBeDestroyed)
        return false;
    auto it = this->_allPlayers.begin();
    for (; it < this->_allPlayers.end(); it++)
        if (*it == toSearch)
            return true;
    return false;
}

bool RType::Server::Room::sendMessageToRoom(const Utils::MessageParsed_s &msg)
{
    if (this->_willBeDestroyed)
        return false;
    std::cout << "message incoming" << std::endl;
    std::pair<std::string, int> toFind({msg.senderIp, msg.senderPort});
    auto it = this->_allPlayers.begin();
    for (; it < this->_allPlayers.end(); it++)
        if (*it == toFind) {
            std::cout << "The player with the port " << it->second << " got a message with the " << static_cast<int>(msg.msgType) << " type " << std::endl;
            //need the ecs to do an action on a certain client when a message is send to him
            return true;
        }
    return false;
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
                msg.senderIp = it.first;
                msg.senderPort = it.second;
                for (int i = 0; i < nbMsg; ++i)
                    this->_socket->send(msg);
            }
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<< "Room " << static_cast<int>(this->_id) << "is running" << std::endl;
        std::cout << "Members of the team --" << std::endl;
        for (auto &it : this->_allPlayers) {
            std::cout << "player : " << it.second << std::endl;
        }
        //need the ecs to do actions
    }
}

bool RType::Server::Room::removeFromRoom(const std::pair<std::string, signed int> &toRemove)
{
    bool isFirst = false;
    if (this->_willBeDestroyed)
        return false;
    for (auto it = this->_allPlayers.begin(); it < this->_allPlayers.end(); it++) {
        if (*it == toRemove) {
            std::cout << "Player " << toRemove.first << " " << toRemove.second << " has been removed from team" << this->_id << std::endl;
            if (it == this->_allPlayers.begin()) {
                isFirst = true;
                _willBeDestroyed = true;
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