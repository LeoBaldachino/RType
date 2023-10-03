/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RTypeGameLoop
*/

#include "RTypeGameLoop.hpp"

RType::RTypeGameLoop::RTypeGameLoop(Core &core) : GameLoop(core)
{
    
}

RType::RTypeGameLoop::~RTypeGameLoop()
{
}

std::queue<RType::Utils::MessageParsed_s> RType::RTypeGameLoop::runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages)
{
    std::queue<RType::Utils::MessageParsed_s> toReturn;
    while (!newMessages.empty()) {
        unsigned short firstShort = newMessages.front().second.getFirstShort();
        std::cout << "New message from id = " << newMessages.front().first << " with message id " << newMessages.front().second.msgType << " and first short" << firstShort << std::endl;
        this->_core._entities[newMessages.front().first]->addMessage(newMessages.front().second);
        newMessages.pop();
    }
    return toReturn;
}