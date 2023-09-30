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

        void setOrigin(Vector2d origin) { this->_origin = origin; }
        void setDirection(Vector2d direction) { this->_direction = direction; }
        void setVelocity(int velocity) { this->_velocity = velocity; }

        Vector2d getOrigin() const { return this->_origin; }
        Vector2d getDirection() const { return this->_direction; }
        int getVelocity() const { return this->_velocity; }

    private:
        Vector2d _origin;
        Vector2d _direction;
        int _velocity;
};
