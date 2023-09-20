/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** State.hpp
*/

#pragma once


class State {
    public:
        State()
        {
            this->_state = true;
            this->_health = 100;
        };
        ~State(){};
        bool getState() const
        {
            return this->_state;
        }
        int getHealth() const
        {
            return this->_health;
        }
        void setState(bool newState)
        {
            this->_state = newState;
        }
        void setHealth(int newHealth)
        {
            this->_health = newHealth;
        }
    private:
        bool _state;
        int _health;

};