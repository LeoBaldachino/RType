/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Inputs.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <vector>

class Inputs {
    public:
        enum Events {
            Up,
            Down,
            Left,
            Right,
            Shoot,
            PiercingShoot,
            CloseWindow,
            Unknown
        };
        Inputs() {};
        ~Inputs() {};
        std::vector<Events> getEvents(void) const { return(this->_events); }
        void addEvents(const Events event) { this->_events.push_back(event); }
    private:
        std::vector<Events> _events;
};
