/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** TourreSystem.cpp
*/

#include "TourreSystem.hpp"

void TourreSystem::updatePos(Tourre &t)
{
    this->_movementSystem.updatePosition(t);
    t.setHasMoved(true);
}

void TourreSystem::createShots(Tourre &t, const Player &player, Core &core)
{
    Shoot tmpShoot(t.shoot(player.getPosition()));
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/enemyShot.png", false), core.getAvailabeIndex());
}
