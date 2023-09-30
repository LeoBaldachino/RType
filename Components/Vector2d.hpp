/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Vector2d.hpp
*/

#pragma once
#include <fstream>
#include <iostream>

class Vector2d {
    public:
        Vector2d(float x, float y) { this->x = x; this->y = y; };
        Vector2d() { this->x = 0; this->y = 0; };
        ~Vector2d() {};
        float x;
        float y;
};
