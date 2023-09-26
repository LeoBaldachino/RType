/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** InputSystem.cpp
*/

#include "InputSystem.hpp"

void InputSystem::handleInput(sf::Event event, std::unique_ptr<sf::RenderWindow> &window)
{
    if (this->_inputs.getEvents().size() == 0)
        this->_inputs.addEvents(Inputs::Events::Unknown);
    if (event.type == sf::Event::KeyReleased)
        if (this->shooting && event.key.code == sf::Keyboard::Space) {
            std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>
            time = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(time - this->shotTime).count() >= 1)
                this->_inputs.addEvents(Inputs::Events::PiercingShoot);
            else
                this->_inputs.addEvents(Inputs::Events::Shoot);
            this->shooting = false;
        }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            this->_inputs.addEvents(Inputs::Events::Up);
        if (event.key.code == sf::Keyboard::Down)
            this->_inputs.addEvents(Inputs::Events::Down);
        if (event.key.code == sf::Keyboard::Left)
            this->_inputs.addEvents(Inputs::Events::Left);
        if (event.key.code == sf::Keyboard::Right)
            this->_inputs.addEvents(Inputs::Events::Right);
        if (event.key.code == sf::Keyboard::Escape)
            this->_inputs.addEvents(Inputs::Events::CloseWindow);
        if (!this->shooting && event.key.code == sf::Keyboard::Space) {
            this->shotTime = std::chrono::steady_clock::now();
            this->shooting = true;
        }
    }
}