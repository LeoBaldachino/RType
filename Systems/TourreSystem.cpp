/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** TourreSystem.cpp
*/

#include "TourreSystem.hpp"

void TourreSystem::setTourre(const Tourre &b)
{
    this->_tourre = b;
}

Tourre TourreSystem::getTourre(void) const
{
    return (this->_tourre);
}

void TourreSystem::updatePos(void)
{
    this->_movementSystem.updatePosition(this->_tourre);
}

void TourreSystem::createShots(const Player &player)
{
    Shoot tmpShoot(this->_tourre.shoot(player.getPosition()));
    // this->_shots.push_back(std::make_unique<ShotSystem>(ShotEntity(tmpShoot)));
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
