/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.cpp
*/

#include "BydosSystem.hpp"

BydosSystem::BydosSystem()
{
}

void BydosSystem::updatePos(Bydos &b)
{
    if (!b.readyToMove())
        return;
    this->_movementSystem.updatePosition(b);
    b.setHasMoved(true);
}

void BydosSystem::createShots(Bydos &b, const Position &playerPos, Core &core)
{
    if (!b.readyToShoot())
        return;
    Shoot tmpShoot(b.shoot(playerPos));
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "Assets/enemyShot.png", false), core.getAvailabeIndex());
}

void BydosSystem::checkCollision(Bydos &b, IEntity &entity, Core &core, bool isPercing)
{
    if (this->_hitBoxSystem.entityIntersect(b, entity)) {
        if (b.getLifes() >= 1)
            if (b.removeOneLife())
                std::cout << "One life removed from bydos" << std::endl;
        if (!isPercing)
            core.removeEntityLater(entity);
    }
}
