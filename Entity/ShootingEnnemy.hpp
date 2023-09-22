/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShootingEnnemy.hpp
*/

#pragma once
#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
#include "../Components/AIShoot.hpp"
#include "../Components/Hitbox.hpp"

class ShootingEnnemy {
    public:
        ShootingEnnemy(Position position, int velocity, Vector2d moveDirection);
        Shoot shoot(const Position &playerPos) const;
    private:
        State _state;
        Position _position;
        Moveable _movement;
};
