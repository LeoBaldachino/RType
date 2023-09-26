/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MovementSystem.cpp
*/

#include "MovementSystem.hpp"

MovementSystem::MovementSystem()
{

}

MovementSystem::~MovementSystem()
{

}

void MovementSystem::updatePosition()
{
    this->_position.setX(this->_position.getX() + this->_moveable.getDirection().x * this->_moveable.getVelocity());
    this->_position.setY(this->_position.getY() + this->_moveable.getDirection().y * this->_moveable.getVelocity());
}
