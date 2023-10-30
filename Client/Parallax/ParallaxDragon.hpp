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

class ParallaxDragon {
    public:
        ParallaxDragon(Texture &texture) : _texture(texture) {};
        void drawDragonParallax(std::unique_ptr<sf::RenderWindow> &window);

    private:
        void drawSky(std::unique_ptr<sf::RenderWindow> &window);
        void handleSkyFrame(void);

        void drawTower(std::unique_ptr<sf::RenderWindow> &window);
        void handleTowerFrame(void);

        void drawClouds(std::unique_ptr<sf::RenderWindow> &window);
        void handleCloudsFrame(void);

        unsigned int _skyFrame = 0;
        unsigned int _towerFrame = 0;
        unsigned int _cloudsFrameFirst = 0;
        unsigned int _cloudsFrameSecond = 0;
        unsigned int _cloudsFrameThird = 0;

        std::chrono::steady_clock::time_point _skyClock;
        std::chrono::steady_clock::time_point _towerClock;
        std::chrono::steady_clock::time_point _cloudsClockFirst;
        std::chrono::steady_clock::time_point _cloudsClockSecond;
        std::chrono::steady_clock::time_point _cloudsClockThird;

        Texture _texture;
        sf::Sprite _sprite;
};
