/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Health
*/

#pragma once
#include <chrono>
#include <iostream>

#define INVINCIBILTY_DURATION 2000

class Health {
    public:
        Health(unsigned char numberOfLifes) {
            this->_lifes = numberOfLifes;
            this->_maxLife = numberOfLifes;
            this->_asBeenHit = false;
            this->_chronoHit = std::chrono::steady_clock::now();
        };
        ~Health() {};
        bool removeOneLife() {
            if (this->isInvincible())
                return false;
            this->_lifes--;
            this->_asBeenHit = true;
            this->_chronoHit = std::chrono::steady_clock::now();
            return true;
        };
        inline bool actuallyInvincible() const {return this->_asBeenHit;};
        inline unsigned char getLifes() const {return this->_lifes;};
        inline void addLife() {this->_lifes < this->_maxLife ? this->_lifes++ : 0;};
        inline void setLife(unsigned char life) {this->_lifes = life;};
        inline unsigned char getMaxLife() const {return this->_maxLife;};
        inline void setMaxLife(unsigned char maxLife){this->_maxLife = maxLife;};
    private:
        bool isInvincible() const {
            if (!this->_asBeenHit)
                return false;
            auto actClock = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(this->_chronoHit - actClock).count() < INVINCIBILTY_DURATION)
                return false;
            return true;
        }
        unsigned char _lifes;
        std::chrono::steady_clock::time_point _chronoHit;
        bool _asBeenHit;
        unsigned char _maxLife;
};
