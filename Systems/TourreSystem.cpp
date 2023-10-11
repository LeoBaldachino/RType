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
    core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "Assets/enemyShot.png"), core.getAvailabeIndex());
}

// void TourreSystem::clearShots(void)
// {
//     for (int i = 0; i != this->_shots.size(); ++i) {
//         if (this->_shots[i] == NULL || this->_shots[i] == nullptr)
//             continue;
//         if (this->_shots[i]->getPos().getX() <= 0
//         || this->_shots[i]->getPos().getY() <= 0
//         || this->_shots[i]->getPos().getX() >= this->_tourre.getPosition().getWidth()
//         || this->_shots[i]->getPos().getY() >= this->_tourre.getPosition().getHeight())
//             this->_shots.erase(std::find(std::begin(this->_shots), std::end(this->_shots), this->_shots[i]));
//     }
// }
