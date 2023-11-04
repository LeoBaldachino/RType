/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DragonSystem.cpp
*/

#include "DragonSystem.hpp"

void DragonSystem::updatePos(Dragon &t)
{
    if (!t.readyToMove())
        return;
    if (t.getPosition().getX() > 1920 - 667)
        t.setPosition(Position(t.getPosition().getX() - 1, t.getPosition().getY()));
    else {
        if (t.getGoingUp()) {
            t.setPosition(Position(t.getPosition().getX(), t.getPosition().getY() - 1));
            if (t.getPosition().getY() < 50)
                t.setGoingUp(false);
        } else {
            t.setPosition(Position(t.getPosition().getX(), t.getPosition().getY() + 1));
            if (t.getPosition().getY() > 400)
                t.setGoingUp(true);
        }
    }
    t.setHasMoved(true);
}

void DragonSystem::checkCollision(Dragon &t, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(t, entity)) {
        if (t.getLifes() >= 1)
            t.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}

void DragonSystem::shot(Dragon &t, Core &core)
{
    if (!t.readyToShoot())
        return;
    DragonShot tmpDragonShot(t.getPosition());
    core.addEntity(std::make_shared<DragonShot>(tmpDragonShot), core.getAvailabeIndex());
}
