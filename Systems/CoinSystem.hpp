/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** CoinSystem.hpp
*/

#pragma once
#include "../Entity/Coin.hpp"
#include "Subsystems/MovementSystem.hpp"

class CoinSystem {
    public:
        CoinSystem() {};
        ~CoinSystem() {};
        void updatePos(Coin &c);
    private:
        MovementSystem _movementSystem;
};
