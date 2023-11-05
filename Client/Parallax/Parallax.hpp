/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Parallax.hpp
*/

#pragma once
#include "../Texture/Texture.hpp"
#include <fstream>
#include <chrono>
#include <iostream>
#include <memory>

class Parallax {
    public:
        Parallax(Texture &texture) : _texture(texture) { this->_parallaxClock = std::chrono::steady_clock::now(); this->_screenFXClock = std::chrono::steady_clock::now();};
        void drawParallax(std::unique_ptr<sf::RenderWindow> &window);
        void drawScreenFX(std::unique_ptr<sf::RenderWindow> &window);
        void drawBackgroundParallax(std::unique_ptr<sf::RenderWindow> &window);
    private:
        void handleParallaxFrame(void);
        void handleScreenFXFrame(void);
        void handleBackgroundParallaxFrame(void);
        unsigned int _parallaxFrame = 1;
        std::chrono::steady_clock::time_point _parallaxClock;
        unsigned int _screenFXFrame = 1;
        std::chrono::steady_clock::time_point _screenFXClock;
        Texture _texture;
        sf::Sprite _sprite;
        unsigned int _skyFrame = 0;
        unsigned int _mountainFrame = 0;
        unsigned int _forestFrame = 0;
        std::chrono::steady_clock::time_point _skyClock;
        std::chrono::steady_clock::time_point _mountainClock;
        std::chrono::steady_clock::time_point _forestClock;
};
