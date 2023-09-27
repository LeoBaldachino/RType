/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.hpp
*/

#pragma once
#include "../Entity/Bydos.hpp"
// #include "Subsystems/DrawSystem.hpp"
#include "Subsystems/ShotSystem.hpp"

class BydosSystem {
    public:
        BydosSystem() {};
        BydosSystem(const Bydos &bydos);
        ~BydosSystem() {};
        void draw(std::unique_ptr<sf::RenderWindow> &window);
        void updatePos(void);
        void updateShots(void);
        void drawShots(std::unique_ptr<sf::RenderWindow> &window);
        void createShots(const Player &player);

    private:
        Bydos _bydos;
        DrawSystem _drawSystem;
        std::vector<std::unique_ptr<ShotSystem>> _shots;

};
