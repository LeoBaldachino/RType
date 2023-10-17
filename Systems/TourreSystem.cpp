/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** TourreSystem.cpp
*/

#include "TourreSystem.hpp"

TourreSystem::TourreSystem()
{
}

void TourreSystem::updatePos(Tourre &t)
{
    if (!t.readyToMove())
        return;
    this->_movementSystem.updatePosition(t);
    t.setHasMoved(true);
}

// void TourreSystem::createShots(Tourre &t, const Player &player, Core &core)
// {
//     Shoot tmpShoot(t.shoot(player.getPosition()));
//     core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/enemyShot.png", false), core.getAvailabeIndex());
// }

void TourreSystem::checkCollision(Tourre &t, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(t, entity)) {
        if (t.getLifes() >= 1)
            if (t.removeOneLife())
                std::cout << "One life removed from tourre" << std::endl;
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}