/**
 * @file Moveable.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Moveable class definition
 */

#pragma once
#include "Vector2d.hpp"

/**
 * @class Moveable
 * @brief Class representing a moveable object
 */
class Moveable {
    public:
        /**
         * @brief Construct a new Moveable object
         * 
         * @param origin The origin of the moveable object
         * @param direction The direction of the moveable object
         * @param velocity The velocity of the moveable object
         */
        Moveable(Vector2d origin, Vector2d direction, int velocity) { this->_origin = origin; this->_direction = direction; this->_velocity = velocity; }

        /**
         * @brief Construct a new Moveable object
         */
        Moveable() {};

        /**
         * @brief Destroy the Moveable object
         */
        ~Moveable() {};

        /**
         * @brief Set the Origin object
         * 
         * @param origin The new origin of the moveable object
         */
        void setOrigin(Vector2d origin) { this->_origin = origin; }

        /**
         * @brief Set the Direction object
         * 
         * @param direction The new direction of the moveable object
         */
        void setDirection(Vector2d direction) { this->_direction = direction; }

        /**
         * @brief Set the Velocity object
         * 
         * @param velocity The new velocity of the moveable object
         */
        void setVelocity(int velocity) { this->_velocity = velocity; }

        /**
         * @brief Get the Origin object
         * 
         * @return Vector2d The origin of the moveable object
         */
        Vector2d getOrigin() const { return this->_origin; }

        /**
         * @brief Get the Direction object
         * 
         * @return Vector2d The direction of the moveable object
         */
        Vector2d getDirection() const { return this->_direction; }

        /**
         * @brief Get the Velocity object
         * 
         * @return int The velocity of the moveable object
         */
        int getVelocity() const { return this->_velocity; }

        

    private:
        Vector2d _origin; /**< The origin of the moveable object */
        Vector2d _direction; /**< The direction of the moveable object */
        int _velocity; /**< The velocity of the moveable object */
};
