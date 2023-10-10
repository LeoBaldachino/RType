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
#include <chrono>

class BydosSystem {
    public:
        BydosSystem();
        ~BydosSystem() {};
        void updatePos(Bydos &b);
        void createShots(Bydos &b, const Player &player, Core &core);

    private:
        MovementSystem _movementSystem;
        std::chrono::steady_clock::time_point _shootClock;
};
