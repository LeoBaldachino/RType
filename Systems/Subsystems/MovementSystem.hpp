/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MovementSystem.hpp
*/

#pragma once
#include "../../Entity/IEntity.hpp"
#include "../../Components/Moveable.hpp"
#include "../../Components/Position.hpp"
#include "../../Components/ClockTimer.hpp"
#include <vector>

class MovementSystem {
    public:
        MovementSystem() {};
        ~MovementSystem() {};
        void updatePosition(IEntity &entity);
};
