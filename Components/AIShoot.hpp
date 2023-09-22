/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** AIShoot.hpp
*/

#pragma once
#include "Vector2d.hpp"
#include "Shoot.hpp"
#include "Position.hpp"

class AIShoot {
    public:
        AIShoot(const Position &playerPos, const Position &shooterPos) { this->_playerPos = playerPos; this->_shooterPos = shooterPos; }
        ~AIShoot() {};
        void setPlayerPos(const Position &playerPos) { this->_playerPos = playerPos; }
        void setShooterPos(const Position &shooterPos) { this->_shooterPos = shooterPos; }
        void setDmg(const int &dmg) { this->_dmg = dmg; }
        void setVelocity(const int &velocity) { this->_velocity = velocity; }
        void setGravity(const float &gravity) { this->_gravity = gravity; }
        Shoot shootLogic() {
            return (Shoot(Vector2d(this->_shooterPos.getX() - this->_playerPos.getX(),
            this->_shooterPos.getY() - this->_playerPos.getY()), Vector2d(this->_shooterPos.getX(), this->_shooterPos.getY()),
            this->_dmg, this->_velocity, this->_gravity, false));
        }
    private:
        Position _playerPos;
        Position _shooterPos;
        int _dmg;
        int _velocity;
        int _gravity;
};
