/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Client.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>

class Client {
    public:
        enum Events {
            Up,
            Down,
            Left,
            Right,
            Shoot,
            PiercingShoot,
            Unknown
        };
        Client();
        ~Client() {};
        bool getIsOpen() const;
        void clearWin() const;
        void refreshWin() const;
        void updateEvents();

    private:
        Client::Events getKeyPressed(sf::Event sfevent);
        std::unique_ptr<sf::RenderWindow> _window;
        std::vector<Events> _events;
        bool _isOpen;
};
