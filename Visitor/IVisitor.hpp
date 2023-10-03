/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IVisitor.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <memory>

class Player;
class Bydos;
class Tourre;

class IVisitor {
    public:
        virtual void visitPlayer(Player &p) = 0;
        virtual void visitBydos(Bydos &b) = 0;
        // virtual void visitTourre(Tourre &t, Player &p, std::unique_ptr<sf::RenderWindow> &window) = 0;
};
