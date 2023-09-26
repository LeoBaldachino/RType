/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Drawable.hpp
*/

#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Drawable {
    public:
        Drawable(std::string textureFile) {
            this->_texture.loadFromFile(textureFile.c_str());
            this->_sprite.setTexture(this->_texture);
        }
        sf::Sprite getSprite(void) const { return(this->_sprite); }
        sf::Texture getTexture(void) const { return(this->_texture); }
        ~Drawable() {};
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
};
