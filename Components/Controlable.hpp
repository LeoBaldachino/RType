/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Controlable.hpp
*/

#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class Controlable {
public:
    Controlable() = default;
    ~Controlable() = default;

    void handleInput(sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    // Handle Up Key Pressed
                    break;
                case sf::Keyboard::Down:
                    // Handle Down Key Pressed
                    break;
                case sf::Keyboard::Left:
                    // Handle Left Key Pressed
                    break;
                case sf::Keyboard::Right:
                    // Handle Right Key Pressed
                    break;
                default:
                    break;
            }
        }
    }
};
