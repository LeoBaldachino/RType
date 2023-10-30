/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** CoinSystem.cpp
*/

#include "CoinSystem.hpp"

void CoinSystem::updatePos(Coin &c)
{
    if (!c.readyToMove())
        return;
    this->_movementSystem.updatePosition(c);
    c.setHasMoved(true);
}
