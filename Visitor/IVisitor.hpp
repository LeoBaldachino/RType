/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IVisitor.hpp
*/

#pragma once
#include <fstream>
#include <iostream>

class Player;

class IVisitor {
    public:
        virtual void visitPlayer(Player &p) = 0;
};
