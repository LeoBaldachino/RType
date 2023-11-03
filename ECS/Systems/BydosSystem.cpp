/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.cpp
*/

#include "BydosSystem.hpp"

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
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/EntitiesSprites/tEnemyShot.png", false, b), core.getAvailabeIndex());
}

void BydosSystem::checkCollision(Bydos &b, IEntity &entity, Core &core, bool isPercing)
{
    if (this->_hitBoxSystem.entityIntersect(b, entity)) {
        if (entity.getEntityType() == RType::playerShoot) {
            try {
                auto shoot = dynamic_cast<ShotEntity &>(entity);
                auto casted = dynamic_cast<Player *>(shoot.getSender());
                casted->increaseScore(0.2);
            } catch (const std::bad_cast &badCast) {
                std::cout << "Bad cast... " << badCast.what() << std::endl;
            }
        }
        if (entity.getEntityType() == RType::percingShoot) {
            try {
                auto shoot = dynamic_cast<PiercingShotEntity &>(entity);
                auto casted = dynamic_cast<Player *>(shoot.getSender());
                casted->increaseScore(0.1);
            } catch (const std::bad_cast &badCast) {
                std::cout << "Bad cast... " << badCast.what() << std::endl;
            }
        }
        if (b.getLifes() >= 1)
            b.removeOneLife();
        if (!isPercing)
            core.removeEntityLater(entity);
    }
}
