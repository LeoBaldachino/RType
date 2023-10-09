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
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "../../Entity/Player.hpp"

class InputSystem {
    public:
        InputSystem() : _inputs() {};
        ~InputSystem() = default;
        void updatePlayer(Player &player);
        // void convertMsgToInputs(Player &player);
        Inputs _inputs;
};
