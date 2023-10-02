/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GameLoop
*/

#include "GameLoop.hpp"

RType::GameLoop::GameLoop(Core &core) : _core(core), 
_commands({
{},
})
{
}

RType::GameLoop::~GameLoop()
{
}

std::queue<RType::Utils::MessageParsed_s> RType::GameLoop::updateGameLoop(std::queue<Utils::MessageParsed_s> queueMsg)
{
    std::queue<Utils::MessageParsed_s> newMessageQueue;
    while (!queueMsg.empty()) {
        auto it = this->_commands.find(queueMsg.front().msgType);
        if (it != this->_commands.end())
            (this->*it->second)(queueMsg.front());
        else
            newMessageQueue.push(queueMsg.front());
        queueMsg.pop();
    }
    return this->runAfterUpdate(newMessageQueue);
}