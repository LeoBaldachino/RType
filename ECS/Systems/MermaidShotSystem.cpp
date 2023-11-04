/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MermaidShotSystem.cpp
*/

#include "MermaidShotSystem.hpp"

void MermaidShotSystem::updatePos(MermaidShot &dS, Position lastPlayerPos)
{
    if (!dS.readyToMove())
        return;
    dS.setPosition(Position(dS.getPosition().getX(), dS.getPosition().getY() - 1));
    dS.setHasMoved(true);
}

void MermaidShotSystem::checkCollision(MermaidShot &dS, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(dS, entity)) {
        if (dS.getLifes() >= 1)
            dS.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}
