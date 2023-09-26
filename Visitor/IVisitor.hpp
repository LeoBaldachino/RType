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
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player;

class IVisitor {
    public:
        virtual void visitPlayer(Player &p, std::unique_ptr<sf::RenderWindow> &window) = 0;
};
