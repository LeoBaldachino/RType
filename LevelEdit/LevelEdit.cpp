/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** LevelEdit
*/

#include <SFML/Graphics.hpp>
#include "LevelEdit.hpp"

LevelEdit::LevelEdit() : _window(sf::VideoMode(1920, 1080), "Level Editor")
{
    if (!_font.loadFromFile("../LevelEdit/Assets/Fonts/AlegreyaSansSC-ExtraBold.ttf"))
        std::cout << "Error loading font" << std::endl;
    _titleText.setFont(_font);
    _titleText.setString("Cuckhead Level Editor");
    _titleText.setCharacterSize(50);
    _titleText.setFillColor(sf::Color::White);
    _titleText.setOutlineColor(sf::Color::Black);
    _titleText.setOutlineThickness(2);
    _titleText.setPosition(0, 0);
    sf::FloatRect textRect = _titleText.getLocalBounds();
    _titleText.setOrigin(textRect.left + (textRect.width / 2.0f), 0.0);
    _titleText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, 20));
}

void LevelEdit::mainLoop()
{

    _window.draw(_titleText);
}

void LevelEdit::run()
{
    std::cout << "Opening Level Editor" << std::endl;
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        _window.clear(sf::Color::White);

        this->mainLoop();

        _window.display();
    }
}
