/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.hpp
*/

#pragma once
#include "../Entity/Bydos.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"

class BydosSystem {
    public:
        BydosSystem() {};
        ~BydosSystem() {};
        void setBydos(const Bydos &b);
        Bydos getBydos(void) const;
        void updatePos(void);
        void updateShots(void);
        // void draw(void);
        // void drawShots(void);
        void createShots(const Player &player);
        void clearShots(void);

    private:
        Bydos _bydos;
        MovementSystem _movementSystem;
        std::unique_ptr<DrawSystem> _drawSystem;
        std::vector<std::unique_ptr<ShotSystem>> _shots;

};
