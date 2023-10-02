/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** main.cpp
*/

#include "Entity/Player.hpp"
#include "Visitor/SystemVisitor.hpp"
#include "Core/Core.hpp"

int main(void)
{
    Core core;
    core.addEntity(std::make_shared<Player>(Position(0, 0, 1080, 1920)), 0);
    core.addEntity(std::make_shared<Bydos>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), 1);
    core.addEntity(std::make_shared<Bydos>(Position(1900, 300, 1080, 1920), 1, Vector2d(-1, 0)), 2);
    std::unique_ptr<sf::RenderWindow> _window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type");
    SystemVisitor v;
    while (_window->isOpen()) {
        _window->clear();
        for (int i = 0; i != core._entities.size(); ++i)
            core._entities[i]->accept(v, _window);
        _window->display();
    }
}
