/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotSystem.hpp
*/

#pragma once
#include <memory>
#include "../../Entity/ShotEntity.hpp"
#include "DrawSystem.hpp"

class ShotSystem {
    public:
        ShotSystem(const ShotEntity &shotEntity);
        ~ShotSystem() {};
        void updatePos(void);
        void draw(std::unique_ptr<sf::RenderWindow> &window, std::string fileName);
        Position getPos(void) const;
    private:
        std::unique_ptr<ShotEntity> _shotEntity;
        std::unique_ptr<DrawSystem> _drawSystem;
};
