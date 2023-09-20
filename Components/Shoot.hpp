/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Shoot.hpp
*/

#pragma once
#include "Vector2d.hpp"

class Shoot {
    public:
        Shoot(Vector2d direction, Vector2d origin, int dmg, int velocity, float gravity, bool whoShot) {
            this->_direction = direction;
            this->_origin = origin;
            this->_dmg = dmg;
            this->_velocity = velocity;
            this->_gravity = gravity;
            this->_whoShot = whoShot;
        }
        ~Shoot() {};
    private:
        Vector2d _direction;
        Vector2d _origin;
        int _dmg;
        int _velocity;
        float _gravity;
        bool _whoShot; // True if shot by the player false otherwise
};
