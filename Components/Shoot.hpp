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

        Vector2d getDirection(void) const { return(this->_direction); }
        Vector2d getOrigin(void) const { return(this->_origin); }
        int getDmg(void) const { return(this->_dmg); }
        int getVelocity(void) const { return(this->_velocity); }
        float getGravity(void) const { return(this->_gravity); }
        bool getWhoShot(void) const { return(this->_whoShot); }
        
        void setDirection(const Vector2d &direction) { this->_direction = direction; }
        void setOrigin(const Vector2d &origin) { this->_origin = origin; }
        void setDmg(const int &dmg) { this->_dmg = dmg; }
        void setVelocity(const int &velocity) { this->_velocity = velocity; }
        void setGravity(const float &gravity) { this->_gravity = gravity; }
        void setWhoShot(const bool &whoShot) { this->_whoShot = whoShot; }
        ~Shoot() {};
    private:
        Vector2d _direction;
        Vector2d _origin;
        int _dmg;
        int _velocity;
        float _gravity;
        bool _whoShot; // True if shot by the player false otherwise
};
