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

    void handleInput(sf::Event event, std::unique_ptr<sf::RenderWindow> &window) {
        if (this->_events.size() == 0)
            this->_events.push_back(Events::Unknown);
        if (event.type == sf::Event::KeyReleased)
            if (this->shooting && event.key.code == sf::Keyboard::Space) {
                std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>
                time = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(time - this->shotTime).count() >= 1)
                    _events.push_back(Events::PiercingShoot);
                else
                    _events.push_back(Events::Shoot);
                this->shooting = false;
            }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up)
                _events.push_back(Events::Up);
            if (event.key.code == sf::Keyboard::Down)
                _events.push_back(Events::Down);
            if (event.key.code == sf::Keyboard::Left)
                _events.push_back(Events::Left);
            if (event.key.code == sf::Keyboard::Right)
                _events.push_back(Events::Right);
            if (event.key.code == sf::Keyboard::Escape)
                _events.push_back(Events::CloseWindow);
            if (!this->shooting && event.key.code == sf::Keyboard::Space) {
                this->shotTime = std::chrono::steady_clock::now();
                this->shooting = true;
            }
        }
    }
    std::vector<Events> _events;
    std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> shotTime;
    bool shooting = false;
};
