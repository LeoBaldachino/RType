/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ParallaxDragon.cpp
*/

#include "ParallaxDragon.hpp"

void ParallaxDragon::handleSkyFrame(void)
{
    auto clock = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_skyClock).count() < 50)
        return;
    this->_skyClock = std::chrono::steady_clock::now();
    ++this->_skyFrame;
    this->_skyFrame = this->_skyFrame >= 1521 ? 0 : this->_skyFrame;
}

void ParallaxDragon::drawSky(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_sprite.setTexture(this->_texture.dragonSky);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_skyFrame, 0, 1521, 780));
    this->_sprite.setScale(1.5, 1.5);
    this->_sprite.setPosition(0, 0);
    window->draw(this->_sprite);
}

void ParallaxDragon::handleCloudsFrame(void)
{
    auto clock = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_cloudsClockFirst).count() < 5)
        return;
    this->_cloudsClockFirst = std::chrono::steady_clock::now();
    ++this->_cloudsFrameFirst;
    this->_cloudsFrameFirst = this->_cloudsFrameFirst >= 2762 ? 0 : this->_cloudsFrameFirst;

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_cloudsClockSecond).count() < 10)
        return;
    this->_cloudsClockSecond = std::chrono::steady_clock::now();
    ++this->_cloudsFrameSecond;
    this->_cloudsFrameSecond = this->_cloudsFrameSecond >= 3116 ? 0 : this->_cloudsFrameSecond;

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_cloudsClockThird).count() < 15)
        return;
    this->_cloudsClockThird = std::chrono::steady_clock::now();
    ++this->_cloudsFrameThird;
    this->_cloudsFrameThird = this->_cloudsFrameThird >= 3015 ? 0 : this->_cloudsFrameThird;

}

void ParallaxDragon::drawClouds(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleCloudsFrame();

    this->_sprite.setTexture(this->_texture.dragonForeCloudsThird);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_cloudsFrameThird, 0, 3015, 198));
    this->_sprite.setScale(1, 1);
    this->_sprite.setPosition(0, 900);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.dragonForeCloudsFirst);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_cloudsFrameFirst, 0, 2762, 80));
    this->_sprite.setScale(1.5, 1.5);
    this->_sprite.setPosition(0, 975);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.dragonForeCloudsSecond);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_cloudsFrameSecond, 0, 3116, 183));
    this->_sprite.setScale(1.5, 1.5);
    this->_sprite.setPosition(0, 875);
    window->draw(this->_sprite);

}

void ParallaxDragon::handleTowerFrame(void)
{
    auto clock = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_towerClock).count() < 50)
        return;
    this->_towerClock = std::chrono::steady_clock::now();
    ++this->_towerFrame;
    this->_towerFrame = this->_towerFrame >= 180 ? 0 : this->_towerFrame;
}

void ParallaxDragon::drawTower(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleTowerFrame();

    this->_sprite.setTexture(this->_texture.tower[this->_towerFrame / 30]);
    this->_sprite.setTextureRect(sf::Rect<int>(464 * (this->_towerFrame % 30), 0, 464, 1094));
    this->_sprite.setScale(0.75, 0.75);
    this->_sprite.setPosition(400, 300);
    window->draw(this->_sprite);
}



void ParallaxDragon::drawDragonParallax(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleSkyFrame();

    this->drawSky(window);
    this->drawTower(window);
    this->drawClouds(window);


}
