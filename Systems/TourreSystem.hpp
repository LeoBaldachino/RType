/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** TourreSystem.hpp
*/

#pragma once
#include "../Entity/Tourre.hpp"
#include "../Core/Core.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/HitBox.hpp"

#include <chrono>

class TourreSystem {
    public:
        TourreSystem() {};
        ~TourreSystem() {};
        void updatePos(Tourre &t);
        void checkCollision(Tourre &t, IEntity &entity, Core &core, bool isTouching);

    private:
        MovementSystem _movementSystem;
        HitBox _hitBoxSystem;
};
