/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** AIShoot.hpp
*/

#pragma once
#include "../../Components/Vector2d.hpp"
#include "../../Components/Shoot.hpp"
#include "../../Components/Position.hpp"

class AIShoot {
    public:
        AIShoot(const Position &playerPos, const Position &shooterPos);
        ~AIShoot() {};
        void setPlayerPos(const Position &playerPos);
        void setShooterPos(const Position &shooterPos);
        void setDmg(const int &dmg);
        void setVelocity(const int &velocity);
        void setGravity(const float &gravity);
        Shoot shootLogic(void);
    private:
        Position _playerPos;
        Position _shooterPos;
        int _dmg;
        float _velocity = 1;
        int _gravity;
};
