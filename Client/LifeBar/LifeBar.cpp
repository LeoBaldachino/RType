/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** LifeBar
*/

#include "LifeBar.hpp"

RType::LifeBar::LifeBar()
{
    this->_texture.create(SCREEN_X, SCREEN_Y);
    this->_sprite.setPosition(sf::Vector2f(0, 0));
    this->arr = (sf::Uint8 *)malloc(sizeof(sf::Uint8) * SCREEN_X * SCREEN_Y * 4 * 8);
    for (int i = 0; i < SCREEN_X * SCREEN_Y * 4 * 8; ++i)
        arr[i] = 120;
    this->_texture.update(this->arr, SCREEN_X, SCREEN_Y, 0, 0);
}

RType::LifeBar::~LifeBar()
{
    std::cout << "Estoy destrudos" << std::endl;
    free(arr);
}


void RType::LifeBar::setLifeBarToPlayer(const std::shared_ptr<Player> &pl)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    Position pos = pl->getPosition();
    unsigned char hp = pl->getLifes();
    pos.setY(pos.getY() + 30);
    for (int i = pos.getX(); i < pos.getX() + (hp * 30); ++i)
        for (int j = pos.getY(); j < pos.getY() + 15; ++j) {
            sf::Color pixels;
            pixels.a = 255;
            pixels.g = 255;
            *(sf::Color * )(4 * (i * SCREEN_X + j) + arr) = pixels;
        }
}

void RType::LifeBar::display(std::unique_ptr<sf::RenderWindow> &window)
{
    // std::unique_lock<std::mutex> lock(this->_mutex);
    // this->_texture.update(this->arr, SCREEN_X, SCREEN_Y, 0, 0);
    // this->_sprite.setTexture(this->_texture);
    // window->draw(this->_sprite);
    // this->clearFrameBuffer();
}

void RType::LifeBar::clearFrameBuffer()
{
    for (unsigned int i = 0; i < SCREEN_X * SCREEN_Y * 4 * 8; ++i)
        arr[i] = 120;   
}