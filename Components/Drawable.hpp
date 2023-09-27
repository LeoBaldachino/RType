/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Drawable.hpp
*/

#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class Drawable {
    public:
        Drawable() {};
        Drawable(std::string textureFile, int scale) {
            this->_texture.loadFromFile(textureFile.c_str());
            this->_sprite.setTexture(this->_texture);
            this->_sprite.scale(sf::Vector2f(scale, scale));
        }
        sf::Sprite getSprite(void) const { return(this->_sprite); }
        sf::Texture getTexture(void) const { return(this->_texture); }
        ~Drawable() {};
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
};
