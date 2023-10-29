/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GenieSystem.hpp
*/

#pragma once
#include "../Entity/Genie.hpp"
#include "../Core/Core.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/HitBox.hpp"

#include <chrono>

class GenieSystem {
    public:
        GenieSystem();
        ~GenieSystem() {};
        void updatePos(Genie &t);
        // void createShots(Genie &t, const Player &player, Core &core);
        void checkCollision(Genie &t, IEntity &entity, Core &core, bool isTouching);

    private:
        MovementSystem _movementSystem;
        HitBox _hitBoxSystem;
};
