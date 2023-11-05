/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Parallax.cpp
*/

#include "Parallax.hpp"

void Parallax::handleParallaxFrame(void)
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_parallaxClock).count() < 50)
        return;
    this->_parallaxClock = std::chrono::steady_clock::now();
    ++this->_parallaxFrame;
    this->_parallaxFrame = this->_parallaxFrame == 288 ? 1 : this->_parallaxFrame;
}

void Parallax::drawParallax(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleParallaxFrame();
    this->_sprite.setTexture(this->_texture.desert[this->_parallaxFrame / 12]);
    this->_sprite.setTextureRect(sf::Rect<int>(1311 * (this->_parallaxFrame % 12), 0, 1311, 560));
    this->_sprite.setScale(1.5, 1.5);
    this->_sprite.setPosition(0, 300);
    window->draw(this->_sprite);
}

void Parallax::handleBackgroundParallaxFrame(void)
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_forestClock).count() < 10)
        return;
    this->_forestClock = std::chrono::steady_clock::now();
    ++this->_forestFrame;
    this->_forestFrame = this->_forestFrame >= 1470 ? 0 : this->_forestFrame;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_mountainClock).count() < 25)
        return;
    this->_mountainClock = std::chrono::steady_clock::now();
    ++this->_mountainFrame;
    this->_mountainFrame = this->_mountainFrame >= 2046 ? 0 : this->_mountainFrame;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_skyClock).count() < 50)
        return;
    this->_skyClock = std::chrono::steady_clock::now();
    ++this->_skyFrame;
    this->_skyFrame = this->_skyFrame >= 2048 ? 0 : this->_skyFrame;
}

void Parallax::drawBackgroundParallax(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleBackgroundParallaxFrame();

    this->_sprite.setTexture(this->_texture.desertSky);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_skyFrame, 0, 1920, 194));
    this->_sprite.setScale(2.5, 2.5);
    this->_sprite.setPosition(0, 0);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.desertMountain);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_mountainFrame, 0, 2046, 101));
    this->_sprite.setScale(2, 2);
    this->_sprite.setPosition(0, 250);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.desertForest);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_forestFrame, 0, 1470, 167));
    this->_sprite.setScale(1.5, 1.5);
    this->_sprite.setPosition(0, 350);
    window->draw(this->_sprite);
}

void Parallax::handleScreenFXFrame(void)
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_screenFXClock).count() < 500)
        return;
    this->_screenFXClock = std::chrono::steady_clock::now();
    ++this->_screenFXFrame;
    this->_screenFXFrame = this->_screenFXFrame == 127 ? 1 : this->_screenFXFrame;
}

void Parallax::drawScreenFX(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleScreenFXFrame();
    this->_sprite.setTexture(this->_texture.screenFX[this->_screenFXFrame / 16]);
    this->_sprite.setTextureRect(sf::Rect<int>(1024 * (this->_screenFXFrame % 16), 0, 1024, 512));
    this->_sprite.setScale(1.875, 1.875);
    this->_sprite.setPosition(0, 0);
    window->draw(this->_sprite);
}
