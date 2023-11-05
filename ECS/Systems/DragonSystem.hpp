/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DragonSystem.hpp
*/

#pragma once
#include "../Entity/Dragon.hpp"
#include "../../Core/Core.hpp"
#include "../Entity/DragonShot.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/HitBox.hpp"
#include <chrono>

class DragonSystem {
    public:
        DragonSystem() {};
        ~DragonSystem() {};
        void updatePos(Dragon &t);
        void checkCollision(Dragon &t, IEntity &entity, Core &core, bool isTouching);
        void shot(Dragon &t, Core &core);
    private:
        MovementSystem _movementSystem;
        HitBox _hitBoxSystem;
};
