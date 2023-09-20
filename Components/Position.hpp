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
        Position(int x, int y, int height, int width) { this->_pos_x = x; this->_pos_y = y; this->_width = width; this->_height = height; }
        ~Position() {};
        int getX() const { return this->_pos_x; }
        int getY() const { return this->_pos_y; }
        void moveUp() { if (this->_pos_y > 0) --this->_pos_y; };
        void moveDown() { if (this->_pos_y < this->_height) ++this->_pos_y; };
        void moveLeft() { if (this->_pos_x > 0) --this->_pos_x; };
        void moveRight() { if (this->_pos_x < this->_width) ++this->_pos_x; };
    private:
        int _pos_x;
        int _pos_y;
        int _width;
        int _height;
};