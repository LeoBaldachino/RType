/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IsReady
*/

#pragma once
#include <chrono>

class IsReady {
    public:
        IsReady(size_t timeout) {
            this->_baseClock = std::chrono::steady_clock::now();
            this->_baseTimeout = timeout;
        };
        ~IsReady() {};
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
    private:
        std::chrono::steady_clock::time_point _baseClock;
        size_t _baseTimeout;
};
