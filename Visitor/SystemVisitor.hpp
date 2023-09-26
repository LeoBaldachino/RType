/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SystemVisitor.hpp
*/

#pragma once
#include "IVisitor.hpp"
#include "../Systems/PlayerSystem.hpp"

class SystemVisitor : public IVisitor {
    public:
        void visitPlayer(Player &p, std::unique_ptr<sf::RenderWindow> &window) {
            PlayerSystem tmpPlayerSystem(p);
            tmpPlayerSystem.draw(window);
        }
};
