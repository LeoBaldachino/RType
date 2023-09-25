/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Walls.cpp
*/

#include "Walls.hpp"

Walls::Walls(Position position, int velocity, Vector2d moveDirection)
{
    this->_position = position;
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}
