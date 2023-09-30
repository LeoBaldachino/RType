/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Walls.hpp
*/

#pragma once

#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/Hitbox.hpp"

class Walls {
    public:
        Walls(Position position, int velocity, Vector2d moveDirection);
        ~Walls(){};
    private:
        Position _position;
        Moveable _movement;
        // Hitbox _hitbox;
};
