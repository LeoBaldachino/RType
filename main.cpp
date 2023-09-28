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
    SystemVisitor v;
    std::vector<std::unique_ptr<IEntity>> entities;
    entities.push_back(std::make_unique<Player>(Position(0, 0, 1080, 1920)));
    entities.push_back(std::make_unique<Bydos>(Position(1900, 100, 1080, 1920), 10, Vector2d(-1, 0)));
    entities.push_back(std::make_unique<Bydos>(Position(1900, 300, 1080, 1920), 10, Vector2d(-1, 0)));
    while (_window->isOpen()) {
        _window->clear();
        for (int i = 0; i != entities.size(); ++i)
            entities[i]->accept(v, _window);
        _window->display();
    }
}
