/**
 * @file Drawable.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Drawable class definition
 */

#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

/**
 * @class Drawable
 * @brief Drawable class handles texture and sprite
 */
class Drawable {
    public:
        /**
         * @brief Construct a new Drawable object
         */
        Drawable() {};

        /**
         * @brief Construct a new Drawable object with texture and scale
         * 
         * @param textureFile Texture file path
         * @param scale Scale factor
         */
        Drawable(std::string textureFile, int scale) {
            this->_texture.loadFromFile(textureFile.c_str());
            this->_sprite.setTexture(this->_texture);
            this->_sprite.scale(sf::Vector2f(scale, scale));
        }

        /**
         * @brief Get the Sprite object
         * 
         * @return sf::Sprite 
         */
        sf::Sprite getSprite(void) const { return(this->_sprite); }

        /**
         * @brief Get the Texture object
         * 
         * @return sf::Texture 
         */
        sf::Texture getTexture(void) const { return(this->_texture); }

        /**
         * @brief Destroy the Drawable object
         */
        ~Drawable() {};
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
};
