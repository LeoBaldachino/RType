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
         * @brief Destroy the State object
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