/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bydos.cpp
*/

#include "Bydos.hpp"

Bydos::Bydos(Position position, int velocity, Vector2d moveDirection)
{
    this->_position = position;
    this->_state = State(100);
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

Shoot Bydos::shoot(const Position &playerPos) const
{   
    AIShoot aiShoot(playerPos, this->_position);
    return aiShoot.shootLogic();
}
