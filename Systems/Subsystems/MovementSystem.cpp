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
    std::vector<int> rangePos = entity.getEntityPositionRange();
    if (rangePos[0] || rangePos[1]) {
        Moveable tmpMv = entity.getMoveable();
        if (entity.getPosition().getY() >= rangePos[0]) {
            tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, -1.0));
            entity.setMoveable(tmpMv);
        }
        if (entity.getPosition().getY() <= rangePos[1]) {
        printf("X : %d Y : %d dir : %f\n", entity.getPosition().getX(), entity.getPosition().getY(), tmpMv.getDirection().y);
            tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, 1.0));
            entity.setMoveable(tmpMv);
        }
    }
    entity.setPosition(Position(entity.getPosition().getX() + entity.getMoveable().getDirection().x * entity.getMoveable().getVelocity(),
    entity.getPosition().getY() + entity.getMoveable().getDirection().y * entity.getMoveable().getVelocity(),
    entity.getPosition().getHeight(), entity.getPosition().getWidth()));
}
