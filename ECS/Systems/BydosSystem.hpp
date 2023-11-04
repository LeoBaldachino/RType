/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.hpp
*/

#pragma once
#include "../Entity/Bydos.hpp"
#include "../Core/Core.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/HitBox.hpp"
#include "Subsystems/PiercingShotSystem.hpp"

#include <chrono>

class BydosSystem {
    public:
        BydosSystem() {};
        ~BydosSystem() {};
        void updatePos(Bydos &b);
        void createShots(Bydos &b, const Position &playerPos, Core &core);
        void checkCollision(Bydos &b, IEntity &entity, Core &core, bool isPercing);
    private:
        MovementSystem _movementSystem;
        HitBox _hitBoxSystem;
};
