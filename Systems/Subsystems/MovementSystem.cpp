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
            if (rangePos[2] == rangePos[3]) {
                tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, -1.0));
                entity.setMoveable(tmpMv);
                entity.setTempoState(0);
            } else {
                tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, 0));
                entity.setMoveable(tmpMv);
                entity.setTempoState(rangePos[2] + 1);
            }

        }
        if (entity.getPosition().getY() <= rangePos[1]) {
            tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, 1.0));
            entity.setMoveable(tmpMv);
        }
    }
    entity.setPosition(Position(entity.getPosition().getX() + entity.getMoveable().getDirection().x * entity.getMoveable().getVelocity(),
    entity.getPosition().getY() + entity.getMoveable().getDirection().y * entity.getMoveable().getVelocity(),
    entity.getPosition().getHeight(), entity.getPosition().getWidth()));
}
