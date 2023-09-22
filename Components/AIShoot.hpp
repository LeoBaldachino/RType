/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** AIShoot.hpp
*/

#pragma once
#include "Vector2d.hpp"
#include "Shoot.hpp"

class AIShoot {
    public:
        AIShoot(Vector2d playerPos, Vector2d shooterPos) { this->_playerPos = playerPos; this->_shooterPos = shooterPos; }
        ~AIShoot() {};
        void setPlayerPos(const Vector2d &playerPos) { this->_playerPos = playerPos; }
        void setShooterPos(const Vector2d &shooterPos) { this->_shooterPos = shooterPos; }
        void setDmg(const int &dmg) { this->_dmg = dmg; }
        void setVelocity(const int &velocity) { this->_velocity = velocity; }
        void setGravity(const float &gravity) { this->_gravity = gravity; }
        Shoot shootLogic() {
            return (Shoot(Vector2d(this->_shooterPos.x - this->_playerPos.x,
            this->_shooterPos.y - this->_playerPos.y), this->_shooterPos,
            this->_dmg, this->_velocity, this->_gravity, false));
        }
    private:
        Vector2d _playerPos;
        Vector2d _shooterPos;
        int _dmg;
        int _velocity;
        int _gravity;
};
