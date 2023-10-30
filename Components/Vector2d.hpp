/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Vector2d.hpp
*/

#pragma once
#include <fstream>
#include <iostream>

/**
 * @class Vector2d
 * @brief Class representing a 2D vector
 */
class Vector2d {
    public:
        /**
         * @brief Construct a new Vector2d object with given x and y
         * @param x The x coordinate
         * @param y The y coordinate
         */
        Vector2d(float x, float y) { this->x = x; this->y = y; };

        /**
         * @brief Construct a new Vector2d object with x and y set to 0
         */
        Vector2d() { this->x = 0; this->y = 0; };

        /**
         * @brief Destroy the Vector2d object
         */
        ~Vector2d() {};

        float x; ///< The x coordinate
        float y; ///< The y coordinate
};
