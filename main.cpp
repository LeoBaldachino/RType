/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** main.cpp
*/

#include "Entity/Player.hpp"
#include "Visitor/SystemVisitor.hpp"

int main(void)
{
    std::unique_ptr<sf::RenderWindow> _window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type");
    Player p(Position(0, 0, 1080, 1920));
    SystemVisitor v;
    while (_window->isOpen()) {
        _window->clear();
        p.accept(v, p, _window);
        _window->display();
    }
}
