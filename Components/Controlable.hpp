/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Controlable.hpp
*/

#pragma once
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>

class Controlable {
public:
    Controlable() = default;
    ~Controlable() = default;
    enum Events {
            Up,
            Down,
            Left,
            Right,
            Shoot,
            PiercingShoot,
            CloseWindow,
            Unknown
    };

    void handleInput(sf::Event event, std::unique_ptr<sf::RenderWindow> window) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    _events.push_back(Events::Up);
                    break;
                case sf::Keyboard::Down:
                    _events.push_back(Events::Down);
                    break;
                case sf::Keyboard::Left:
                    _events.push_back(Events::Left);
                    break;
                case sf::Keyboard::Right:
                    _events.push_back(Events::Right);
                    break;
                case sf::Keyboard::Escape:
                    _events.push_back(Events::CloseWindow);
                case sf::Keyboard::Space:
                    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>
                    shootTime = std::chrono::steady_clock::now();
                    sf::Event tmpEvent;
                    while (tmpEvent.type != sf::Event::KeyReleased)
                        window->pollEvent(tmpEvent);
                    auto time = std::chrono::steady_clock::now();
                    if (std::chrono::duration_cast<std::chrono::seconds>(time - shootTime).count() >= 1)
                        _events.push_back(Events::PiercingShoot);
                    else
                        _events.push_back(Events::Shoot);
                default:
                    break;
            }
        }
    }
    std::vector<Events> _events;
};
