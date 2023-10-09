// /*
// ** EPITECH PROJECT, 2023
// ** B-CPP-500-MLH-5-1-rtype-robin.denni
// ** File description:
// ** Bonus.hpp
// */

// #pragma once

#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
#include "../Components/Hitbox.hpp"
#include "IEntity.hpp"

class Bonus {
    public:
        Bonus(Position position, int velocity, Vector2d moveDirection);
        ~Bonus(){};
        bool isColidingWith(IEntity &entity);
        Vector2d getSize(void);
    private:
        // State _state;
        Position _position;
        Moveable _movement;
        Vector2d _size;
        // Hitbox _hitbox;
};