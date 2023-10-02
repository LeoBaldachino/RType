/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Core.cpp
*/

#include "Core.hpp"

Core::Core()
{

}

bool Core::addEntity(const std::shared_ptr<IEntity> &entity, unsigned short index)
{
    if (this->_entities.find(index) != this->_entities.end())
        return false;
    this->_entities.insert({index, entity});
    return true;
}

unsigned short Core::getAvailabeIndex()
{
    if (this->_presentIndex.empty())
        return static_cast<unsigned short>(this->_entities.size());
    unsigned short newId = this->_presentIndex.front();
    this->_presentIndex.pop();
    return newId;
}

bool Core::removeEntity(unsigned short id)
{
    auto it = this->_entities.find(id);
    if (it == this->_entities.end())
        return false;
    this->_entities.erase(it);
    this->_presentIndex.push(id);
    return true;
}