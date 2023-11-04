/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RTypeGameLoop
*/

#include "RTypeGameLoop.hpp"

RType::RTypeGameLoop::RTypeGameLoop(Core &core) : GameLoop(core)
{
    auto clock = std::chrono::steady_clock::now();
    this->_refreshAllEntities = clock;
    this->_refreshPlayers = clock;
    this->_refreshStatus = clock;
}

void RType::RTypeGameLoop::updatePlayerPos(std::pair<unsigned short, Utils::MessageParsed_s> msg)
{
    auto it = this->_core._entities.find(msg.first);
    if (it == this->_core._entities.end())
        return;
    if (it->second->getEntityType() != RType::player)
        return;
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(it->second);
    player->_inputs->lockInputs();
    for (unsigned char i = 0; i < 7; ++i) {
        if (msg.second.bytes[i] > 6)
            break;
        if (static_cast<bool>(player->_inputs))
            player->_inputs->addEvents((Inputs::Events)msg.second.bytes[i]);
    }
    player->_inputs->unlockInputs();
}


std::queue<RType::Utils::MessageParsed_s> RType::RTypeGameLoop::runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages)
{
    std::queue<RType::Utils::MessageParsed_s> toReturn;
    while (!newMessages.empty()) {
        if (newMessages.front().second.msgType == 14)
            this->updatePlayerPos(newMessages.front());
        newMessages.pop();
    }
    this->handleWaves(toReturn);
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_refreshAllEntities).count() < REFRESH_ALL_ENTITIES)
        this->sendRefreshPlayers(toReturn);
    else {
        this->sendNbOfEntites(toReturn);
        this->sendRefreshAllEntities(toReturn);
        this->_refreshAllEntities = clock;
    }
    this->refreshStatus(toReturn);
    size_t entitySize = this->_core._entities.size();
    for (auto &it : this->_core._entities)
        it.second->accept(this->v, this->_core);
    if (entitySize != this->_core._entities.size()) {
        std::cout << "Auto refresh..." << std::endl;
        this->sendRefreshAllEntities(toReturn);
    }
    std::queue<unsigned short> toErase = this->_core.getToErase();
    this->_core.eraseEntity();
    while (!toErase.empty()) {
        std::cout << "Erase entity..." << std::endl;
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

void RType::RTypeGameLoop::handleCoin(std::queue<Utils::MessageParsed_s> &toReturn)
{
    auto it = this->_coin.begin();
    std::queue<unsigned short> toDelete;
    Utils::MessageParsed_s msg;
    msg.msgType = removeEntity;
    for (; it != this->_coin.end(); it++) {
        auto finded = this->_core._entities.find(*it);
        if (finded == this->_core._entities.end()) {
            toDelete.push(*it);
            continue;
        }
        Position actPos = finded->second->getPosition();
        if (actPos.getX() < 0 || actPos.getY() < 0) {
            this->_core.removeEntityLater(finded->first);
            toDelete.push(*it);
            continue;
        }
    }
    while (!toDelete.empty()) {
        msg.setFirstShort(toDelete.front());
        toReturn.push(msg);
        for (auto it = this->_coin.begin(); it < this->_coin.end(); it++)
            if (*it == toDelete.front())
                this->_coin.erase(it);
        toDelete.pop();
    }
    msg.msgType = entityType;
}

void RType::RTypeGameLoop::handleBydos(std::queue<RType::Utils::MessageParsed_s> &toReturn)
{
    auto it = this->_bydos.begin();
    std::queue<unsigned short> toDelete;
    Utils::MessageParsed_s msg;
    msg.msgType = removeEntity;
    for (; it != this->_bydos.end(); it++) {
        auto finded = this->_core._entities.find(*it);
        if (finded == this->_core._entities.end()) {
            toDelete.push(*it);
            continue;
        }
        Position actPos = finded->second->getPosition();
        if (actPos.getX() < 0 || actPos.getY() < 0) {
            this->_core.removeEntityLater(finded->first);
            toDelete.push(*it);
            continue;
        }
    }
    while (!toDelete.empty()) {
        msg.setFirstShort(toDelete.front());
        toReturn.push(msg);
        for (auto it = this->_bydos.begin(); it < this->_bydos.end(); it++)
            if (*it == toDelete.front())
                this->_bydos.erase(it);
        toDelete.pop();
    }
    msg.msgType = entityType;
}

void RType::RTypeGameLoop::handleWaves(std::queue<RType::Utils::MessageParsed_s> &toReturn)
{
    if (this->_waves.size() != 0 && this->_bydos.size() == 0 && this->_tourre.size() == 0) {
        Utils::MessageParsed_s msg;
        while (this->_tourre.size() < this->_waves[0][Parser::Enemies::TOURRE]) {
            unsigned short id = this->_core.getAvailabeIndex();
            this->_tourre.push_back(id);
            msg.setFirstShort(id);
            msg.setSecondShort(tourre);
            toReturn.push(msg);
            this->_core.addEntity(std::make_shared<Tourre>(Position(1500 + std::rand() % 200, 1080 - 53, 1080, 1920), 1, Vector2d(-1, -1)), id);
        }
        while (this->_bydos.size() < this->_waves[0][Parser::Enemies::BYDOS]) {
            unsigned short id = this->_core.getAvailabeIndex();
            this->_bydos.push_back(id);
            msg.setFirstShort(id);
            msg.setSecondShort(bydos);
            toReturn.push(msg);
            this->_core.addEntity(std::make_shared<Bydos>(Position(1700 + std::rand() % 200, std::rand() % 1000, 1080, 1920), 1, Vector2d(-1, 0)), id);
        }
        while (this->_coin.size() < this->_waves[0][Parser::Enemies::COIN]) {
            unsigned short id = this->_core.getAvailabeIndex();
            this->_coin.push_back(id);
            msg.setFirstShort(id);
            msg.setSecondShort(coin);
            toReturn.push(msg);
            this->_core.addEntity(std::make_shared<Coin>(Position(1700 + std::rand() % 200, std::rand() % 1000, 1080, 1920)), id);
        }
        this->_waves.erase(this->_waves.begin());
    }
}

void RType::RTypeGameLoop::handleTourre(std::queue<RType::Utils::MessageParsed_s> &toReturn)
{
    auto it = this->_tourre.begin();
    std::queue<unsigned short> toDelete;
    Utils::MessageParsed_s msg;
    msg.msgType = removeEntity;
    for (; it != this->_tourre.end(); it++) {
        auto finded = this->_core._entities.find(*it);
        if (finded == this->_core._entities.end()) {
            toDelete.push(*it);
            continue;
        }
        Position actPos = finded->second->getPosition();
        if (actPos.getX() < 0 || actPos.getY() < 0) {
            this->_core.removeEntityLater(finded->first);
            toDelete.push(*it);
            continue;
        }
    }
    while (!toDelete.empty()) {
        msg.setFirstShort(toDelete.front());
        toReturn.push(msg);
        for (auto it = this->_tourre.begin(); it < this->_tourre.end(); it++)
            if (*it == toDelete.front())
                this->_tourre.erase(it);
        toDelete.pop();
    }
    msg.msgType = entityType;
}

void RType::RTypeGameLoop::addRemoveEntity(std::queue<Utils::MessageParsed_s> &toReturn, unsigned short id)
{
    Utils::MessageParsed_s msg;
    msg.msgType = removeEntity;
    msg.setFirstShort(id);
    toReturn.push(msg);
}

void RType::RTypeGameLoop::checkPlayerStatus(std::queue<Utils::MessageParsed_s> &toReturn)
{
    Utils::MessageParsed_s msgToSend;
    msgToSend.msgType = valueSet;
    for (auto it : this->_playerArray) {
        auto find = this->_core._entities.find(it);
        if (find == this->_core._entities.end())
            continue;
        if (find->second->getEntityType() != player)
            continue;
        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(find->second);
        msgToSend.setFirstShort(it);
        msgToSend.bytes[3] = player->getLifes();
        // msgToSend.bytes[4] = player->actuallyInvincible() ? 1 : 0;
        msgToSend.bytes[5] = player->getMaxLife();
        msgToSend.bytes[4] = player->getScore();
        toReturn.push(msgToSend);
    }
}


void RType::RTypeGameLoop::sendRefreshAllEntities(std::queue<Utils::MessageParsed_s> &toReturn)
{
    this->handleBydos(toReturn);
    this->handleTourre(toReturn);
    for (auto it : this->_core._entities) {
        // if (it.second->getHasMoved()) {
            Position tmpPos = it.second->getPosition();
            Utils::MessageParsed_s msgReturned;
            msgReturned.setFirstShort(tmpPos.getX());
            msgReturned.setSecondShort(tmpPos.getY());
            msgReturned.setThirdShort(it.first);
            msgReturned.bytes[6] = it.second->getEntityType();
            msgReturned.msgType = moveAnEntity;
            toReturn.push(msgReturned);
        // }
    }
}

void RType::RTypeGameLoop::sendRefreshPlayers(std::queue<Utils::MessageParsed_s> &toReturn)
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::microseconds>(clock - this->_refreshPlayers).count() < REFRESH_PLAYERS)
        return;
    this->_refreshPlayers = clock;
    for (auto it : this->_playerArray) {
        auto find = this->_core._entities.find(it);
        if (find == this->_core._entities.end())
            continue;
        find->second->accept(this->v, this->_core);
        Position tmpPos = find->second->getPosition();
        Utils::MessageParsed_s msgReturned;
        msgReturned.setFirstShort(tmpPos.getX());
        msgReturned.setSecondShort(tmpPos.getY());
        msgReturned.setThirdShort(find->first);
        msgReturned.bytes[6] = find->second->getEntityType();
        msgReturned.msgType = moveAnEntity;
        toReturn.push(msgReturned);
    }
}

void RType::RTypeGameLoop::checkBydosStatus(std::queue<Utils::MessageParsed_s> &toReturn)
{
    Utils::MessageParsed_s msgToSend;
    msgToSend.msgType = valueSet;
    for (auto it : this->_bydos) {
        auto find = this->_core._entities.find(it);
        if (find == this->_core._entities.end())
            continue;
        if (find->second->getEntityType() != bydos)
            continue;
        std::shared_ptr<Bydos> bydos = std::dynamic_pointer_cast<Bydos>(find->second);
        msgToSend.setFirstShort(it);
        msgToSend.bytes[3] = bydos->getLifes();
        msgToSend.bytes[4] = bydos->actuallyInvincible() ? 1 : 0;
        toReturn.push(msgToSend);
    }
}

void RType::RTypeGameLoop::checkTourreStatus(std::queue<Utils::MessageParsed_s> &toReturn)
{
    Utils::MessageParsed_s msgToSend;
    msgToSend.msgType = valueSet;
    for (auto it : this->_tourre) {
        auto find = this->_core._entities.find(it);
        if (find == this->_core._entities.end())
            continue;
    if (find->second->getEntityType() != tourre)
        continue;
    std::shared_ptr<Tourre> tourre = std::dynamic_pointer_cast<Tourre>(find->second);
    msgToSend.setFirstShort(it);
    msgToSend.bytes[3] = tourre->getLifes();
    msgToSend.bytes[4] = tourre->actuallyInvincible() ? 1 : 0;
    toReturn.push(msgToSend);
    }
}

void RType::RTypeGameLoop::setEnemiesWaves(std::vector<std::map<Parser::Enemies, int>> waves)
{
    this->_waves = waves;
}


void RType::RTypeGameLoop::refreshStatus(std::queue<Utils::MessageParsed_s> &toReturn)
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_refreshStatus).count() < STATUS_ALL_ENTITES)
        return;
    this->_refreshStatus = clock;
    this->checkPlayerStatus(toReturn);
    this->checkBydosStatus(toReturn);
    this->checkTourreStatus(toReturn);
}

void RType::RTypeGameLoop::sendNbOfEntites(std::queue<Utils::MessageParsed_s> &toReturn)
{
    // std::cout << "Entities size is " << this->_core._entities.size() << std::endl;
    Utils::MessageParsed_s msg;
    msg.msgType = nbOfEntities;
    msg.setFirstShort(static_cast<unsigned short>(this->_core._entities.size()));
    toReturn.push(msg);
}
