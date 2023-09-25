/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bydos.hpp
*/

#pragma once
#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Components/Hitbox.hpp"

class Bydos {
    public:
        Bydos(Position position, int velocity, Vector2d moveDirection);
        Shoot shoot(const Position &playerPos) const;
    private:
        State _state;
        Position _position;
        Moveable _movement;
};
