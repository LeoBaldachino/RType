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

class TourreSystem {
    public:
        TourreSystem() {};
        ~TourreSystem() {};
        void updatePos(Tourre &t);
        void createShots(Tourre &t, const Player &player, Core &core);

    private:
        MovementSystem _movementSystem;
        std::vector<std::unique_ptr<ShotSystem>> _shots;
};
