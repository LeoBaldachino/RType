/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

RType::GameLoop::GameLoop(Core &core) : _core(core), 
_commands({
{newPlayerConnected, &RType::GameLoop::addPlayer},
{playerDeconnected, &RType::GameLoop::removePlayer},
})
{
}

RType::GameLoop::~GameLoop()
{
}

std::queue<RType::Utils::MessageParsed_s> RType::GameLoop::updateGameLoop(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> queueMsg)
{
    std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessageQueue;
    while (!queueMsg.empty()) {
        auto it = this->_commands.find(queueMsg.front().second.msgType);
        if (it != this->_commands.end())
            (this->*it->second)(queueMsg.front().second, queueMsg.front().first);
        else
            newMessageQueue.push(queueMsg.front());
        queueMsg.pop();
    }
    return this->runAfterUpdate(newMessageQueue);
}


void RType::GameLoop::setPositionEntityFromMsg(const Utils::MessageParsed_s &msg, unsigned short id)
{

}

void RType::GameLoop::spawnEntityFromMsg(const Utils::MessageParsed_s &msg, unsigned short id)
{

}

void RType::GameLoop::addPlayer(const Utils::MessageParsed_s &msg, unsigned short id)
{
    for (auto it = this->_playerArray.begin(); it < this->_playerArray.end(); it++)
        if (*it == id) {
            std::cout << "Already in the tab..." << std::endl;
            return;
        }
    this->_playerArray.push_back(id);
    std::cout << "Add player " << id << " To the tab " << std::endl;
}

void RType::GameLoop::removePlayer(const Utils::MessageParsed_s &msg, unsigned short id)
{
    std::cout << "Start remove player" << std::endl;
    for (auto it = this->_playerArray.begin(); it < this->_playerArray.end(); it++)
        if (*it == id) {
            this->_playerArray.erase(it);
            std::cout << "Remove player " << id << " of the tab " << std::endl;
            return;
        }
    std::cout << "This player does not exist..." << std::endl;
}

std::tuple<unsigned short, unsigned short, unsigned short> RType::GameLoop::getPlayerDetails(unsigned char playerId)
{
    if (playerId > this->_playerArray.size())
        return std::make_tuple<unsigned short, unsigned short, unsigned short>(0, 0, 0);
    unsigned short id = this->_playerArray[playerId];
    auto it = this->_core._entities.find(id);
    if (it->second->getEntityType() != player)
        return std::make_tuple<unsigned short, unsigned short, unsigned short>(0, 0, 0);
    std::shared_ptr<Player> playerPtr = std::dynamic_pointer_cast<Player>(it->second);
    auto pos = playerPtr->getPosition();
    return std::make_tuple<unsigned short, unsigned short, unsigned short>(pos.getX(), pos.getY(), playerPtr->getLifes());
}