/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotSystem.hpp
*/

#pragma once
#include "../../Entity/ShotEntity.hpp"
#include "DrawSystem.hpp"

class ShotSystem {
    public:
        ShotSystem(const ShotEntity &shotEntity);
        void updatePos(void);
        void draw(std::unique_ptr<sf::RenderWindow> &window);
    private:
        ShotEntity _shotEntity;
        DrawSystem _drawSystem;
};
