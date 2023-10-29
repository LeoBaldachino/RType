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

void MovementSystem::updatePosition(IEntity& entity)
{
    std::vector<float> rangePos = entity.getEntityPositionRange();
    Vector2d lastDirection = entity.getMoveable().getDirection();
    Moveable tmpMv = entity.getMoveable();
    bool waited = false;
    if (rangePos[0] || rangePos[1]) {
        if (!entity.getTempoState().clockOk()) {
            tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, 0));
            entity.setMoveable(tmpMv);
            std::cout << entity.getTempoState().getRemainingTime() << std::endl;
            waited = true;
        }
        if (entity.getPosition().getY() >= rangePos[0]) {
            tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, -1.0));
            entity.setMoveable(tmpMv);
            entity.setTempoState(ClockTimer(rangePos[3]));
        }
        if (entity.getPosition().getY() <= rangePos[1]) {
            tmpMv.setDirection(Vector2d(tmpMv.getDirection().x, 1.0));
            entity.setMoveable(tmpMv);
            entity.setTempoState(ClockTimer(rangePos[2]));
        }
    }
    entity.setPosition(Position(entity.getPosition().getX() + entity.getMoveable().getDirection().x * entity.getMoveable().getVelocity(),
        entity.getPosition().getY() + entity.getMoveable().getDirection().y * entity.getMoveable().getVelocity(),
        entity.getPosition().getHeight(), entity.getPosition().getWidth()));
    if (waited) {
        tmpMv.setDirection(lastDirection);
        entity.setMoveable(tmpMv);
    }
}
