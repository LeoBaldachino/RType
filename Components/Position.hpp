/**
 * @file Position.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Position class definition
 */

#pragma once
#include <fstream>
#include <iostream>

/**
 * @class Position
 * @brief Class representing a position object
 */
class Position {
    public:
        /**
         * @brief Construct a new Position object
         * 
         * @param x The x-coordinate of the position object (default: 0)
         * @param y The y-coordinate of the position object (default: 0)
         * @param height The height of the position object (default: 1080)
         * @param width The width of the position object (default: 1920)
         */
        Position(int x = 0, int y = 0, int height = 1080, int width = 1920) { this->_pos_x = x; this->_pos_y = y; this->_width = width; this->_height = height; }

        /**
         * @brief Destroy the Position object
         */
        ~Position() {};

        /**
         * @brief Get the X-coordinate
         * 
         * @return int The x-coordinate
         */
        int getX() const { return this->_pos_x; }

        /**
         * @brief Get the Y-coordinate
         * 
         * @return int The y-coordinate
         */
        int getY() const { return this->_pos_y; }

        /**
         * @brief Get the Height
         * 
         * @return int The height
         */
        int getHeight() const { return this->_height; }

        /**
         * @brief Get the Width
         * 
         * @return int The width
         */
        int getWidth() const { return this->_width; }

        /**
         * @brief Set the X-coordinate
         * 
         * @param x The x-coordinate
         */
        void setX(int x) { this->_pos_x = x; }

        /**
         * @brief Set the Y-coordinate
         * 
         * @param y The y-coordinate
         */
        void setY(int y) { this->_pos_y = y; }
    private:
        int _pos_x;
        int _pos_y;
        int _width;
        int _height;
};
