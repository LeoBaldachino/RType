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
        if (t.getLifes() >= 1)
            t.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}
