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
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::bydosShoot, false, core.getEntityId(b)), core.getAvailabeIndex());
}

void BydosSystem::checkCollision(Bydos &b, IEntity &entity, Core &core, bool isPercing)
{
    if (this->_hitBoxSystem.entityIntersect(b, entity)) {
        if (entity.getEntityType() == RType::playerShoot) {
            auto shoot = dynamic_cast<ShotEntity &>(entity);
            auto find = core._entities.find(shoot.getSender());
            if (find != core._entities.end() && find->second->getEntityType() == RType::player) {
                auto casted = std::dynamic_pointer_cast<Player>(find->second);
                casted->increaseScore(0.2);
            }
        }
        if (entity.getEntityType() == RType::percingShoot) {
            auto shoot = dynamic_cast<PiercingShotEntity &>(entity);
            auto find = core._entities.find(shoot.getSender());
            if (find != core._entities.end() && find->second->getEntityType() == RType::player) {
                auto casted = std::dynamic_pointer_cast<Player>(find->second);
                casted->increaseScore(0.02);
            }
        }
        if (b.getLifes() >= 1)
            b.removeOneLife();
        if (!isPercing)
            core.removeEntityLater(entity);
    }
}
