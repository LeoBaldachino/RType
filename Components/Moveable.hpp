/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Moveable.hpp
*/

#pragma once
#include "Vector2d.hpp"

class Moveable {
    public:
        Moveable(Vector2d origin, Vector2d direction, int velocity) { this->_origin = origin; this->_direction = direction; this->_velocity = velocity; }
        Moveable() {};
        ~Moveable() {};
    private:
        Vector2d _origin;
        Vector2d _direction;
        int _velocity;
};
