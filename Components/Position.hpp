/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Position.hpp
*/

#pragma once
#include <fstream>
#include <iostream>

class Position {
    public:
        Position(int x = 0, int y = 0, int height = 1080, int width = 1920) { this->_pos_x = x; this->_pos_y = y; this->_width = width; this->_height = height; }
        ~Position() {};
        int getX() const { return this->_pos_x; }
        int getY() const { return this->_pos_y; }
    private:
        int _pos_x;
        int _pos_y;
        int _width;
        int _height;
};
