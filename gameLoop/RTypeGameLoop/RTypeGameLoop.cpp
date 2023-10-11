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
    this->handleBydos(toReturn);
    for (auto it : this->_core._entities) {
        it.second->accept(this->v, this->_core);
        if (true) {
            Position tmpPos = it.second->getPosition();
            Utils::MessageParsed_s msgReturned;
            msgReturned.setFirstShort(tmpPos.getX());
            msgReturned.setSecondShort(tmpPos.getY());
            msgReturned.setThirdShort(it.first);
            msgReturned.msgType = 11;
        }
    }
    return toReturn;
}

RType::EntityTypes RType::RTypeGameLoop::getEntityType(unsigned short id)
{
    for (auto it : this->_playerArray)
        if (it == id)
            return player;
    for (auto it : this->_bydos)
        if (it == id)
            return bydos;
    //search for other types in other arrays
    return none;
}

void RType::RTypeGameLoop::handleBydos(std::queue<RType::Utils::MessageParsed_s> &toReturn)
{
    auto it = this->_bydos.begin();
    std::queue<std::vector<unsigned short>::iterator> toDelete;
    Utils::MessageParsed_s msg;
    msg.msgType = removeEntity;
    for (; it != this->_bydos.end(); it++) {
        auto finded = this->_core._entities.find(*it);
        if (finded == this->_core._entities.end()) {
            toDelete.push(it);
            continue;
        }
        Position actPos = finded->second->getPosition();
        if (actPos.getX() < 0 || actPos.getY() < 0) {
            std::cout << "Entity not not well positionned" << std::endl;
            this->_core.removeEntity(finded->first);
            toDelete.push(it);
            continue;
        }
    }
    while (!toDelete.empty()) {
        std::cout << "Delete a bydos" << std::endl;
        msg.setFirstShort(*toDelete.front());
        toReturn.push(msg);
        this->_bydos.erase(toDelete.front());
        toDelete.pop();
    }
    msg.msgType = entityType;
    if (this->_bydos.size() < 2) {
        std::cout << "Add new bydos" << std::endl;
        unsigned short id = this->_core.getAvailabeIndex();
        this->_bydos.push_back(id);
        msg.setFirstShort(id);
        msg.bytes[3] = bydos;
        this->_core.addEntity(std::make_shared<Bydos>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), id);
    }
}