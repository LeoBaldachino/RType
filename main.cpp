/*
** EPITECH PROJECT, 2023
** TestECS
** File description:
** main.cpp
*/

#include "Core/Core.hpp"

int main(void)
{
    srand(time(NULL));
    Core core;
    Shoot t(Vector2d(1, 0), Vector2d(10, 10), 5, 1, 1, true);
    core.addEntity(std::make_shared<Player>(Position(0, 0, 1080, 1920)), core.getAvailabeIndex());
    core.addEntity(std::make_shared<Bydos>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), core.getAvailabeIndex());
    core.addEntity(std::make_shared<Bydos>(Position(1900, 300, 1080, 1920), 1, Vector2d(-1, 0)), core.getAvailabeIndex());
    core.addEntity(std::make_shared<ShotEntity>(t), core.getAvailabeIndex());
    std::unique_ptr<sf::RenderWindow> _window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type");
    SystemVisitor v;
    while (_window->isOpen()) {
        _window->clear();
        for (auto it : core._entities) {
            it.second->accept(v, core);
            it.second->drawEntity(_window);
        }
        _window->display();
    }
    return (0);
}
