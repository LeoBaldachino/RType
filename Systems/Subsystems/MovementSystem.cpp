/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MovementSystem.cpp
*/

#include "MovementSystem.hpp"

MovementSystem::MovementSystem()
{

}

MovementSystem::~MovementSystem()
{

}

void MovementSystem::updatePosition(IEntity &entity)
{
    entity.setPosition(Position(entity.getPosition().getX() + entity.getMoveable().getDirection().x * entity.getMoveable().getVelocity(),
    entity.getPosition().getY() + entity.getMoveable().getDirection().y * entity.getMoveable().getVelocity(),
    entity.getPosition().getHeight(), entity.getPosition().getWidth()));
}
