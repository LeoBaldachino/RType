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

void RType::GameLoop::addPlayer(const Utils::MessageParsed_s &msg, unsigned short id)
{
    for (auto it = this->_playerArray.begin(); it < this->_playerArray.end(); it++)
        if (*it == id)
            return;
    this->_playerArray.push_back(id);
}

void RType::GameLoop::removePlayer(const Utils::MessageParsed_s &msg, unsigned short id)
{
    for (auto it = this->_playerArray.begin(); it < this->_playerArray.end(); it++)
        if (*it == id) {
            this->_playerArray.erase(it);
            return;
        }
    std::cout << "This player does not exist..." << std::endl;
}
