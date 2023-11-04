/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DragonShotSystem.cpp
*/

#include "DragonShotSystem.hpp"

void DragonShotSystem::updatePos(DragonShot &dS, Position lastPlayerPos)
{
    if (!dS.readyToMove())
        return;
    if (dS.getPosition().getX() < lastPlayerPos.getX())
        dS.setPosition(Position(dS.getPosition().getX() + 1, dS.getPosition().getY()));
    if (dS.getPosition().getX() > lastPlayerPos.getX())
        dS.setPosition(Position(dS.getPosition().getX() - 1, dS.getPosition().getY()));
    if (dS.getPosition().getY() < lastPlayerPos.getY())
        dS.setPosition(Position(dS.getPosition().getX(), dS.getPosition().getY() + 1));
    if (dS.getPosition().getY() > lastPlayerPos.getY())
        dS.setPosition(Position(dS.getPosition().getX(), dS.getPosition().getY() - 1));
    dS.setHasMoved(true);
}

void DragonShotSystem::checkCollision(DragonShot &dS, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(dS, entity)) {
        if (dS.getLifes() >= 1)
            dS.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}
