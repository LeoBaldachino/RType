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
        void draw(std::unique_ptr<sf::RenderWindow> &window);
        void updatePos(void);
        void updateShots(void);
        void drawShots(std::unique_ptr<sf::RenderWindow> &window);
        void createShots(const Player &player);
        void clearShots(void);

    private:
        Tourre _tourre;
        MovementSystem _movementSystem;
        std::unique_ptr<DrawSystem> _drawSystem;
        std::vector<std::unique_ptr<ShotSystem>> _shots;
};
