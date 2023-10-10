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
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(this->_core._entities[msg.first]);
    Position posTmp = player->getPosition();
    RType::Utils::MessageParsed_s msgReturned;

    msg.second.msgType == 14;
    player->_inputs.addEvents((Inputs::Events) msg.second.getFirstShort());
    msgReturned.setFirstShort(posTmp.getX());
    msgReturned.setSecondShort(posTmp.getY());
    msgReturned.setThirdShort(msg.first);
    msgReturned.msgType = 11;
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
    for (auto it : this->_playerArray)
        this->v.visitPlayer(*std::dynamic_pointer_cast<Player>(this->_core._entities[it]), this->_core);
    return toReturn;
}

RType::EntityTypes RType::RTypeGameLoop::getEntityType(unsigned short id)
{
    for (auto it : this->_playerArray)
        if (it == id)
            return player;
    //search for other types in other arrays
    return none;
}