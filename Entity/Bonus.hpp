/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bonus.hpp
*/

#pragma once

#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
#include "../Components/AIShoot.hpp"
#include "../Components/Hitbox.hpp"

class Bonus {
    public:
        Bonus(Position position, int velocity, Vector2d moveDirection);
        ~Bonus(){};
    private:
        // State _state;
        Position _position;
        Moveable _movement;
        // Hitbox _hitbox;
};