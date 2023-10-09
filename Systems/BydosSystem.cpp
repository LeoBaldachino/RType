/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.cpp
*/

#include "BydosSystem.hpp"

void BydosSystem::setBydos(const Bydos &b)
{
    this->_bydos = b;
}

Bydos BydosSystem::getBydos(void) const
{
    return (this->_bydos);
}

void BydosSystem::updatePos(void)
{
    this->_movementSystem.updatePosition(this->_bydos);
}

void BydosSystem::createShots(const Player &player, Core &core)
{
    Shoot tmpShoot(this->_bydos.shoot(player.getPosition()));
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "Assets/enemyShot.png"), core.getAvailabeIndex());
}

// void BydosSystem::clearShots(void)
// {
//     for (int i = 0; i != this->_shots.size(); ++i) {
//         if (this->_shots[i] == NULL || this->_shots[i] == nullptr)
//             continue;
//         if (this->_shots[i]->getPos().getX() <= 0
//         || this->_shots[i]->getPos().getY() <= 0
//         || this->_shots[i]->getPos().getX() >= this->_bydos.getPosition().getWidth()
//         || this->_shots[i]->getPos().getY() >= this->_bydos.getPosition().getHeight())
//             this->_shots.erase(std::find(std::begin(this->_shots), std::end(this->_shots), this->_shots[i]));
//     }
// }
