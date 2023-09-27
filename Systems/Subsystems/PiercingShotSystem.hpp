/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotSystem.hpp
*/

#pragma once
#include "../../Entity/PiercingShotEntity.hpp"
#include "ShotSystem.hpp"

class PiercingShotSystem {
    public:
        PiercingShotSystem(const PiercingShotEntity &piercingShotEntity);
        void updatePos(void);
        void draw(std::unique_ptr<sf::RenderWindow> &window);
    private:
        PiercingShotEntity _piercingShotEntity;
        DrawSystem _drawSystem;
};
