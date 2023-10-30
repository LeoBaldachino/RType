/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** InputSystem.hpp
*/

#pragma once
#include "../../Components/Inputs.hpp"
#include <chrono>
#include <unordered_map>
#include "../../Entity/Player.hpp"

class InputSystem {
    public:
        InputSystem() {};
        ~InputSystem() = default;
        void updatePlayer(Player &player);
};
