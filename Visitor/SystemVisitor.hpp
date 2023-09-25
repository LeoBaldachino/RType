/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SystemVisitor.hpp
*/

#pragma once
#include "IVisitor.hpp"

class SystemVisitor : public IVisitor {
    public:
        void visitPlayer(Player &p) {
            std::cout << "PLAYER" << std::endl;
        }
};
