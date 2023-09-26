/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MovementSystem.hpp
*/

#pragma once

#include "../../Components/Moveable.hpp"
#include "../../Components/Position.hpp"


class MovementSystem {
    public:
        MovementSystem();
        ~MovementSystem();

        void updatePosition();

    private:
        Moveable _moveable;
        Position _position;
};