/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GenieSystem.cpp
*/

#include "GenieSystem.hpp"

GenieSystem::GenieSystem()
{
}

void GenieSystem::updatePos(Genie &t)
{
    if (!t.readyToMove())
        return;
    if (t.getPosition().getX() > 1920 - 500)
        t.setPosition(Position(t.getPosition().getX() - 1, t.getPosition().getY()));
    else {
        if (t.getGoingUp()) {
            t.setPosition(Position(t.getPosition().getX(), t.getPosition().getY() - 1));
            if (t.getPosition().getY() < 50)
                t.setGoingUp(false);
        } else {
            t.setPosition(Position(t.getPosition().getX(), t.getPosition().getY() + 1));
            if (t.getPosition().getY() > 500)
                t.setGoingUp(true);
        }
    }
    t.setHasMoved(true);
}

// void GenieSystem::createShots(Genie &t, const Player &player, Core &core)
// {
//     Shoot tmpShoot(t.shoot(player.getPosition()));
//     core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/enemyShot.png", false), core.getAvailabeIndex());
// }

void GenieSystem::checkCollision(Genie &t, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(t, entity)) {
        if (t.getLifes() >= 1)
            if (t.removeOneLife())
                std::cout << "One life removed from Genie" << std::endl;
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}