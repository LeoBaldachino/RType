/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** StateSystem.hpp
*/

#pragma once

#include "../../Components/State.hpp"

class StateSystem {
    public:
        StateSystem(const State &state);
        ~StateSystem() {};
        void setState(const State &state);
    private:
        State _state;
};