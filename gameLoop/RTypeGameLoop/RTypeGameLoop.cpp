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

void RType::RTypeGameLoop::updatePlayerPos(std::pair<unsigned short, Utils::MessageParsed_s> msg)
{
    auto it = this->_core._entities.find(msg.first);
    if (it == this->_core._entities.end())
        return;
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(it->second);
    Position posTmp = player->getPosition();
    player->_inputs.addEvents((Inputs::Events) msg.second.getFirstShort());
}


std::queue<RType::Utils::MessageParsed_s> RType::RTypeGameLoop::runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages)
{
    std::queue<RType::Utils::MessageParsed_s> toReturn;
    while (!newMessages.empty()) {
        if (newMessages.front().second.msgType == 14)
            this->updatePlayerPos(newMessages.front());
        newMessages.pop();
    }
    this->handleBydos(toReturn);
    for (auto it : this->_core._entities) {
        it.second->accept(this->v, this->_core);
        if (it.second->getHasMoved()) {
            Position tmpPos = it.second->getPosition();
            Utils::MessageParsed_s msgReturned;
            msgReturned.setFirstShort(tmpPos.getX());
            msgReturned.setSecondShort(tmpPos.getY());
            msgReturned.setThirdShort(it.first);
            msgReturned.msgType = moveAnEntity;
            toReturn.push(msgReturned);
        }
    }
    std::queue<unsigned short> toErase = this->_core.getToErase();
    this->_core.eraseEntity();
    while (!toErase.empty()) {
        this->addRemoveEntity(toReturn, toErase.front());
        toErase.pop();
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
    for (auto it : this->_core._entities)
        if (it.first == id)
            return castEntity(it.second->getEntityType());
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
        msg.setSecondShort(bydos);
        toReturn.push(msg);
        if (id == 0)
            std::cout << "Entity 0 is bydos !" << std::endl;
        this->_core.addEntity(std::make_shared<Bydos>(Position(1900, 100 * this->_bydos.size(), 1080, 1920), 1, Vector2d(-1, 0)), id);
    }
}

void RType::RTypeGameLoop::addRemoveEntity(std::queue<Utils::MessageParsed_s> &toReturn, unsigned short id)
{
    Utils::MessageParsed_s msg;
    msg.msgType = removeEntity;
    msg.setFirstShort(id);
    toReturn.push(msg);
}