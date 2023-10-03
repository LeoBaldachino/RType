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

RType::Utils::MessageParsed_s RType::RTypeGameLoop::updatePlayerPos(std::pair<unsigned short, Utils::MessageParsed_s> msg)
{
    std::shared_ptr<IEntity> player = this->_core._entities[msg.first];
    Position posTmp = player->getPosition();
    RType::Utils::MessageParsed_s msgReturned;

    msg.second.msgType == 14;
    msg.second.getFirstShort();
    if (msg.second.getFirstShort() == 3 && posTmp.getX() < 1920) {
        posTmp.setX(posTmp.getX() + 1 * player->getVelocity());
    }
    if (msg.second.getFirstShort() == 2 && posTmp.getX() > 0) {
        posTmp.setX(posTmp.getX() - 1 * player->getVelocity());
    }
    if (msg.second.getFirstShort() == 1 && posTmp.getY() < 1080) {
        posTmp.setY(posTmp.getY() + 1 * player->getVelocity());
    }
    if (msg.second.getFirstShort() == 0 && posTmp.getY() > 0) {
        posTmp.setY(posTmp.getY() - 1 * player->getVelocity());
    }
    player->setPosition(posTmp);
    msgReturned.setFirstShort(posTmp.getX());
    msgReturned.setSecondShort(posTmp.getY());
    msgReturned.setThirdShort(msg.first);
    msgReturned.msgType = 14;
    return msgReturned;
}


std::queue<RType::Utils::MessageParsed_s> RType::RTypeGameLoop::runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages)
{
    std::queue<RType::Utils::MessageParsed_s> toReturn;
    while (!newMessages.empty()) {
        unsigned short firstShort = newMessages.front().second.getFirstShort();
        std::cout << "New message from id = " << newMessages.front().first << " with message id " << newMessages.front().second.msgType << " and first short" << firstShort << std::endl;
        if (newMessages.front().second.msgType == 14)
            toReturn.push(this->updatePlayerPos(newMessages.front()));
        newMessages.pop();
    }
    return toReturn;
}