/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** InputSystem.hpp
*/

#pragma once
#include "../../Components/Inputs.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "../../Entity/Player.hpp"

class InputSystem {
    public:
        InputSystem() : _inputs() {};
        ~InputSystem() = default;
        void handleInput(sf::Event event, std::unique_ptr<sf::RenderWindow> &window);
        void updatePlayer(Player &player);

        Inputs _inputs;
        std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> shotTime;
        bool shooting = false;
};