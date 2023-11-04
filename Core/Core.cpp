/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Core.cpp
*/

#include "Core.hpp"

bool Core::addEntity(std::shared_ptr<IEntity> entity, unsigned short index)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    if (this->_entities.find(index) != this->_entities.end())
        return false;
    this->_entities.insert({index, entity});
    return true;
}

unsigned short Core::getAvailabeIndex()
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    if (this->_presentIndex.empty())
        return static_cast<unsigned short>(this->_entities.size());
    unsigned short newId = this->_presentIndex.front();
    this->_presentIndex.pop();
    return newId;
}

bool Core::removeEntity(IEntity &entity)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    for (auto it : this->_entities)
        if (it.second.get() == &entity) {
            unsigned short tmpId = it.first;
            auto suppr = this->_entities.find(it.first);
            this->_entities.erase(suppr);
            this->_presentIndex.push(tmpId);
            return (true);
        }
    return (false);
}

bool Core::removeEntity(unsigned short id)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    auto it = this->_entities.find(id);
    if (it == this->_entities.end())
        return false;
    this->_entities.erase(it);
    this->_presentIndex.push(id);
    return true;
}

bool Core::removeEntityLater(IEntity &entity)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    for (auto it : this->_entities)
        if (it.second.get() == &entity) {
            unsigned short tmpId = it.first;
            auto suppr = this->_entities.find(it.first);
            this->_erase.push(tmpId);
            return (true);
        }
    return (false);
}

bool Core::removeEntityLater(unsigned short id)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    auto it = this->_entities.find(id);
    if (it == this->_entities.end())
        return false;
    this->_erase.push(id);
    return true;
}

void Core::eraseEntity(void)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    while (!this->_erase.empty()) {
        this->_entities.erase(this->_erase.front());
        this->_presentIndex.push(this->_erase.front());
        this->_erase.pop();
    }
}

unsigned short Core::getEntityId(IEntity &entity)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    for (auto it : this->_entities)
        if (it.second.get() == &entity)
            return it.first;
    return 0;   
}