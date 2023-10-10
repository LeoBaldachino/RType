/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.cpp
*/

#include "BydosSystem.hpp"

BydosSystem::BydosSystem()
{
    this->_shootClock = std::chrono::steady_clock::now();
}

void BydosSystem::updatePos(Bydos &b)
{
    this->_movementSystem.updatePosition(b);
}

void BydosSystem::createShots(Bydos &b, const Player &player, Core &core)
{
    if (!b.readyToShoot())
        return;
    Shoot tmpShoot(b.shoot(player.getPosition()));
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "Assets/enemyShot.png"), core.getAvailabeIndex());
}
