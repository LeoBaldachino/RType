/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include "../Visitor/IVisitor.hpp"

class IEntity {
    public:
        virtual void accept(IVisitor &v, std::unique_ptr<sf::RenderWindow> &window) = 0;
        // virtual void accept(IVisitor &v, Player &p, std::unique_ptr<sf::RenderWindow> &window) = 0;
};
