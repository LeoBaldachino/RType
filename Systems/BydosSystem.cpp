/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.cpp
*/

#include "BydosSystem.hpp"

void BydosSystem::updatePos(Bydos &b)
{
    this->_movementSystem.updatePosition(b);
}

void BydosSystem::createShots(Bydos &b, const Player &player, Core &core)
{
    Shoot tmpShoot(b.shoot(player.getPosition()));
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
