/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** TourreSystem.cpp
*/

#include "TourreSystem.hpp"

void TourreSystem::updatePos(Tourre &t)
{
    if (!t.readyToMove())
        return;
    this->_movementSystem.updatePosition(t);
    t.setHasMoved(true);
}

void TourreSystem::checkCollision(Tourre &t, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(t, entity)) {
        if (entity.getEntityType() == RType::playerShoot) {
            auto shoot = dynamic_cast<ShotEntity &>(entity);
            auto find = core._entities.find(shoot.getSender());
            if (find != core._entities.end() && find->second->getEntityType() == RType::player) {
                auto casted = std::dynamic_pointer_cast<Player>(find->second);
                casted->increaseScore(0.4);
            }
        }
        if (entity.getEntityType() == RType::percingShoot) {
            auto shoot = dynamic_cast<PiercingShotEntity &>(entity);
            auto find = core._entities.find(shoot.getSender());
            if (find != core._entities.end() && find->second->getEntityType() == RType::player) {
                auto casted = std::dynamic_pointer_cast<Player>(find->second);
                casted->increaseScore(0.04);
            }
        }
        if (t.getLifes() >= 1)
            t.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}
