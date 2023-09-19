/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client()
{
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type");
    // this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Fullscreen);
    this->_isOpen = true;
}

bool Client::getIsOpen() const
{
    return (this->_isOpen);
}

void Client::clearWin() const
{
    this->_window->clear();
}

void Client::refreshWin() const
{
    this->_window->display();
}

Client::Events Client::getKeyPressed(sf::Event sfevent)
{
    if (sfevent.key.code == sf::Keyboard::Up)
        return Client::Events::Up;    
    if (sfevent.key.code == sf::Keyboard::Down)
        return Client::Events::Down;
    if (sfevent.key.code == sf::Keyboard::Left)
        return Client::Events::Left;
    if (sfevent.key.code == sf::Keyboard::Right)
        return Client::Events::Right;
    if (sfevent.key.code == sf::Keyboard::Space) {
        std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>
        shootTime = std::chrono::steady_clock::now();
        sf::Event tmpEvent;
        while (tmpEvent.type != sf::Event::KeyReleased)
            this->_window->pollEvent(tmpEvent);
        auto time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(time - shootTime).count() >= 1)
            return Client::Events::PiercingShoot;
        else
            return Client::Events::Shoot;
    }
    if (sfevent.key.code == sf::Keyboard::Escape)
        this->_isOpen = false;
    return Client::Events::Unknown;
}

void Client::updateEvents()
{
    sf::Event sfevent;

    while (this->_window->pollEvent(sfevent)) {
        if (sfevent.type == sf::Event::Closed)
            this->_isOpen = false;
        if (sfevent.type == sf::Event::KeyPressed)
            this->_events.push_back(getKeyPressed(sfevent));
    }
}
