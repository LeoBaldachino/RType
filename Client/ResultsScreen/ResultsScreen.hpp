/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ResultsScreen.hpp
*/

#pragma once

#include "../Texture/Texture.hpp"
#include <chrono>
#include <iostream>
#include <memory>

class ResultsScreen {
    public:
        ResultsScreen(Texture &texture) : _texture(texture)
        {
            this->_font = texture._resultsFont;
        };
        void drawResultsScreen(std::unique_ptr<sf::RenderWindow> &window);
    private:

        Texture _texture;
        sf::Sprite _sprite;
        sf::Text _text;
        sf::Font _font;

};