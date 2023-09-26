/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.hpp
*/

#pragma once
#include "../Entity/Player.hpp"
#include "Subsystems/DrawSystem.hpp"

class PlayerSystem {
    public:
        PlayerSystem() {};
        PlayerSystem(const Player &player);
        ~PlayerSystem() {};
        void draw(std::unique_ptr<sf::RenderWindow> &window);
    private:
        Player _player;
};