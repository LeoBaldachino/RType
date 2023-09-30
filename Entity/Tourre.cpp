/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Tourre.cpp
*/

#include "Tourre.hpp"

Tourre::Tourre(Position position, int velocity, Vector2d moveDirection)
{
    this->_position = position;
    this->_state = State(100);
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

Shoot Tourre::shoot(const Position &playerPos) const
{
    AIShoot aiShoot(playerPos, this->_position);
    return aiShoot.shootLogic();
}

