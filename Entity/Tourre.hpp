/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Tourre.hpp
*/

#pragma once

#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
#include "../Components/AIShoot.hpp"
#include "../Components/Hitbox.hpp"

class Tourre {
    public:
        Tourre(Position position, int velocity, Vector2d moveDirection);
        ~Tourre(){};
        Shoot shoot(const Position &playerPos) const;
    private:
        State _state;
        Position _position;
        Moveable _movement;
        // Hitbox _hitbox;
};