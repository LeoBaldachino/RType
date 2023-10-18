/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ClockTimer
*/

#pragma once
#include <chrono>

class ClockTimer {
    public:
        ClockTimer(size_t timeout) {
            this->_baseClock = std::chrono::steady_clock::now();
            this->_baseTimeout = timeout;
        };
        ~ClockTimer() {};
        bool clockOk() {
            auto clock = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_baseClock).count() < this->_baseTimeout)
                return false;
            this->_baseClock = std::chrono::steady_clock::now();
            return true;
        };
        bool clockOk(size_t timeout) {
            auto clock = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_baseClock).count() < timeout)
                return false;
            this->_baseClock = std::chrono::steady_clock::now();
            return true;
        };
        unsigned long long getRemainingTime() {
            auto clock = std::chrono::steady_clock::now();
            return this->_baseTimeout - std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_baseClock).count();
        };
    private:
        std::chrono::steady_clock::time_point _baseClock;
        size_t _baseTimeout;
};
