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

class ParallaxGnome {
    public:
        ParallaxGnome(Texture &texture) : _texture(texture) {};
        void drawGnomeParallax(std::unique_ptr<sf::RenderWindow> &window);

    private:
        void drawStaticSky(std::unique_ptr<sf::RenderWindow> &window);

        void drawFarElements(std::unique_ptr<sf::RenderWindow> &window);
        void drawMidElements(std::unique_ptr<sf::RenderWindow> &window);
        void drawNearElements(std::unique_ptr<sf::RenderWindow> &window);

        void drawAloneClouds(std::unique_ptr<sf::RenderWindow> &window);


        void handleAloneCloudsFrame(void);
        void handleCloudsFrame(void);

        unsigned int _aloneCloudOneFrame = 0;
        unsigned int _aloneCloudTwoFrame = 0;
        unsigned int _aloneCloudThreeFrame = 0;
        
        unsigned int _largeCloudsFrame = 0;
        unsigned int _mediumCloudsFrame = 0;
        unsigned int _smallCloudsFrame = 0;

        unsigned int _groundFrame = 0;

        std::chrono::steady_clock::time_point _aloneCloudsClock;

        std::chrono::steady_clock::time_point _largeCloudsClock;
        std::chrono::steady_clock::time_point _mediumCloudsClock;
        std::chrono::steady_clock::time_point _smallCloudsClock;

        std::chrono::steady_clock::time_point _groundClock;

        Texture _texture;
        sf::Sprite _sprite;
};
