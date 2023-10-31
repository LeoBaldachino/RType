/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ResultsScreen.cpp
*/

#include "ResultsScreen.hpp"


void ResultsScreen::drawResultsScreen(std::unique_ptr<sf::RenderWindow> &window)
{
    // this->_sprite.setTexture(this->_texture.resScreen);
    this->_sprite.setPosition(0, 0);
    window->draw(this->_sprite);

    this->_text.setFont(this->_font);
    this->_text.setString("TIME................");
    this->_text.setCharacterSize(35);
    this->_text.setFillColor(sf::Color::White);
    this->_text.setPosition(1050, 580);
    window->draw(this->_text);
}