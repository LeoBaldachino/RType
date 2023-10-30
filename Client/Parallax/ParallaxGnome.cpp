/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ParallaxGnome.cpp
*/

#include "ParallaxGnome.hpp"

void ParallaxGnome::drawStaticSky(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_sprite.setTexture(this->_texture.gnomeSky);
    this->_sprite.setTextureRect(sf::Rect<int>(0, 0, 2024, 404));
    this->_sprite.setScale(2, 2);
    this->_sprite.setPosition(0, 0);
    window->draw(this->_sprite);
}

void ParallaxGnome::drawFarElements(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_sprite.setTexture(this->_texture.gnomeFarMountains);
    this->_sprite.setTextureRect(sf::Rect<int>(0, 0, 2019, 148));
    this->_sprite.setScale(1, 1);
    this->_sprite.setPosition(0, 549);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.gnomeSmallClouds);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_largeCloudsFrame, 0, 2131, 90));
    this->_sprite.setScale(0.5, 0.5);
    this->_sprite.setPosition(350, 623);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.gnomeMountainsSecond);
    this->_sprite.setTextureRect(sf::Rect<int>(0, 0, 1420, 313));
    this->_sprite.setScale(1, 1);
    this->_sprite.setPosition(304, 481);
    window->draw(this->_sprite);
}

void ParallaxGnome::drawMidElements(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_sprite.setTexture(this->_texture.gnomeMediumClouds);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_mediumCloudsFrame, 0, 4168, 237));
    this->_sprite.setScale(0.5, 0.5);
    this->_sprite.setPosition(0, 623);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.gnomeMidMountains);
    this->_sprite.setTextureRect(sf::Rect<int>(0, 0, 825, 147));
    this->_sprite.setScale(1, 1);
    this->_sprite.setPosition(500, 643);
    window->draw(this->_sprite);

    this->_sprite.setPosition(1250, 593);
    window->draw(this->_sprite);

    this->_sprite.setTexture(this->_texture.gnomeMediumClouds);
    this->_sprite.setTextureRect(sf::Rect<int>(this->_smallCloudsFrame, 0, 4168, 237));
    this->_sprite.setScale(0.5, 0.5);
    this->_sprite.setPosition(0, 673);
    window->draw(this->_sprite);

}

void ParallaxGnome::drawNearElements(std::unique_ptr<sf::RenderWindow> &window)
{

    this->_sprite.setTexture(this->_texture.gnomeMountainsFirst);
    this->_sprite.setTextureRect(sf::Rect<int>(0, 0, 2028, 757));
    this->_sprite.setScale(1, 1);
    this->_sprite.setPosition(0, 323);
    window->draw(this->_sprite);
}


void ParallaxGnome::handleAloneCloudsFrame(void)
{

}

void ParallaxGnome::drawAloneClouds(std::unique_ptr<sf::RenderWindow> &window)
{

}

void ParallaxGnome::handleCloudsFrame(void)
{
    auto clock = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_smallCloudsClock).count() < 10)
        return;
    this->_smallCloudsClock = std::chrono::steady_clock::now();
    ++this->_smallCloudsFrame;
    this->_smallCloudsFrame = this->_smallCloudsFrame >= 2131 ? 0 : this->_smallCloudsFrame;

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_mediumCloudsClock).count() < 20)
        return;
    this->_mediumCloudsClock = std::chrono::steady_clock::now();
    ++this->_mediumCloudsFrame;
    this->_mediumCloudsFrame = this->_mediumCloudsFrame >= 2026 ? 0 : this->_mediumCloudsFrame;

    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_largeCloudsClock).count() < 30)
        return;
    this->_largeCloudsClock = std::chrono::steady_clock::now();
    ++this->_largeCloudsFrame;
    this->_largeCloudsFrame = this->_largeCloudsFrame >= 2022 ? 0 : this->_largeCloudsFrame;
}

void ParallaxGnome::drawGnomeParallax(std::unique_ptr<sf::RenderWindow> &window)
{
    this->handleCloudsFrame();
    this->drawStaticSky(window);
    this->drawFarElements(window);
    this->drawMidElements(window);
    this->drawNearElements(window);
}
