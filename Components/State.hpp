/**
 * @file State.hpp
 * @author EPITECH PROJECT, 2023
 * @brief State class definition
 */

#pragma once

/**
 * @class State
 * @brief Class representing a State object
 */
class State {
    public:
        /**
         * @brief Construct a new State object
         * @param health The initial health of the state (default is 100)
         */
        State(int health = 100)
        {
            this->_state = true;
            this->_health = health;
        };

        /**
         * @brief Destroy the State object/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** State.hpp
*/

#pragma once


class State {
    public:
        State(int health = 100)
        {
            this->_state = true;
            this->_health = health;
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
         */
        ~State(){};

        /**
         * @brief Get the State object
         * @return bool The current state
         */
        bool getState() const
        {
            return this->_state;
        }

        /**
         * @brief Get the Health of the state
         * @return int The current health
         */
        int getHealth() const
        {
            return this->_health;
        }

        /**
         * @brief Set the State object
         * @param newState The new state to set
         */
        void setState(bool newState)
        {
            this->_state = newState;
        }

        /**
         * @brief Set the Health of the state
         * @param newHealth The new health to set
         */
        void setHealth(int newHealth)
        {
            this->_health = newHealth;
        }

    private:
        bool _state; ///< The state
        int _health; ///< The health
};