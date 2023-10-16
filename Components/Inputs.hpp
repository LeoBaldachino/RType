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
#include <mutex>

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
        inline bool isEmpty() const {return this->_events.empty();};
        inline void addEvents(const Events &event) { this->_events.push(event); }
        inline void popEvent(void) { this->_events.pop(); }
        inline Events getLastEvent() {return this->_events.front();};
        inline void setInput(const std::queue<Events> &newEvents) {this->_events = newEvents;};
        inline void lockInputs() {this->_mutex.lock();};
        inline void unlockInputs() {this->_mutex.unlock();};
    private:
        std::queue<Events> _events;
        std::mutex _mutex;
};
