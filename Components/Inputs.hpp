/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Inputs.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <queue>

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
        std::queue<Events> getEvents(void) const { return(this->_events); }
        inline void addEvents(const Events &event) { this->_events.push(event); }
        inline void popEvent(void) { this->_events.pop(); }
    private:
        std::queue<Events> _events;
};
