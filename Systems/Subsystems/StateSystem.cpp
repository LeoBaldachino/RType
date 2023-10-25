/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** StateSystem.cpp
*/

#include "StateSystem.hpp"

StateSystem::StateSystem(const State &state)
{
    this->_state = state;
}

void StateSystem::setState(const State &state)
{
    this->_state = state;
}
