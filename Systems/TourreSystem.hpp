/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** TourreSystem.hpp
*/

#pragma once
#include "../Entity/Tourre.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"

class TourreSystem {
    public:
        TourreSystem() {};
        ~TourreSystem() {};
        void setTourre(const Tourre &t);
        Tourre getTourre(void) const;
        void updatePos(void);
        void createShots(const Player &player);

    private:
        Tourre _tourre;
        MovementSystem _movementSystem;
        std::vector<std::unique_ptr<ShotSystem>> _shots;
};
