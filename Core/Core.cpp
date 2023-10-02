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

void Core::addEntity(const std::shared_ptr<IEntity> &entity, unsigned short index)
{
    this->_entities[index] = entity;
}
