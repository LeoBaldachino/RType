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
    this->arr = (sf::Uint8 *)std::malloc(sizeof(sf::Uint8) * SCREEN_X * SCREEN_Y * 4 * 8);
    for (int i = 0; i < SCREEN_X * SCREEN_Y * 4 * 8; ++i)
        arr[i] = 0;
    this->_texture.update(this->arr, SCREEN_X, SCREEN_Y, 0, 0);
    this->_updatePixels = std::chrono::steady_clock::now();
}

RType::LifeBar::~LifeBar()
{
    std::free(arr);
}


void RType::LifeBar::setLifeBarToPlayer(const std::shared_ptr<Player> &pl)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    Position pos = pl->getPosition();
    unsigned char hp = pl->getLifes();
    unsigned char diffHp = pl->getMaxLife() - hp;
    if (pos.getY() < 30)
        return;
    pos.setY(pos.getY() - 30);
    for (int i = pos.getX(); i < pos.getX() + (hp * 30); ++i)
        for (int j = pos.getY(); j < pos.getY() + 5; ++j) {
            sf::Color pixels;
            pixels.a = 255;
            pixels.g = 255;
            *(sf::Color * )(4 * (j * SCREEN_X + i) + arr) = pixels;
            this->_toErase.push({i, j});
        }
    for (int i = pos.getX() + (hp * 30); i < pos.getX() + (hp * 30) + (diffHp * 30); ++i)
        for (int j = pos.getY(); j < pos.getY() + 5; ++j) {
            sf::Color pixels;
            pixels.a = 255;
            pixels.r = 255;
            *(sf::Color * )(4 * (j * SCREEN_X + i) + arr) = pixels;
            this->_toErase.push({i, j});
        }
}


void RType::LifeBar::setLifeBarToBydos(const std::shared_ptr<Bydos> &by)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    Position pos = by->getPosition();
    unsigned char hp = by->getLifes();
    unsigned char diffHp = by->getMaxLife() - hp;
    if (pos.getY() < 30)
        return;
    pos.setY(pos.getY() - 30);
    for (int i = pos.getX(); i < pos.getX() + (hp * 30); ++i)
        for (int j = pos.getY(); j < pos.getY() + 5; ++j) {
            sf::Color pixels;
            pixels.a = 255;
            pixels.g = 255;
            *(sf::Color * )(4 * (j * SCREEN_X + i) + arr) = pixels;
            this->_toErase.push({i, j});
        }
    for (int i = pos.getX() + (hp * 30); i < pos.getX() + (hp * 30) + (diffHp * 30); ++i)
        for (int j = pos.getY(); j < pos.getY() + 5; ++j) {
            sf::Color pixels;
            pixels.a = 255;
            pixels.r = 255;
            *(sf::Color * )(4 * (j * SCREEN_X + i) + arr) = pixels;
            this->_toErase.push({i, j});
        }
}

void RType::LifeBar::display(std::unique_ptr<sf::RenderWindow> &window)
{
    std::unique_lock<std::mutex> lock(this->_mutex);
    window->draw(this->_sprite);
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_updatePixels).count() < UPDATE_PIXEL_TIME)
        return;
    this->_updatePixels = clock;
    this->_texture.update(this->arr, SCREEN_X, SCREEN_Y, 0, 0);
    this->_sprite.setTexture(this->_texture);
    this->clearFrameBuffer();
}

void RType::LifeBar::clearFrameBuffer()
{
    sf::Color pixels;
    pixels.a = 0;
    pixels.g = 0;
    while (!this->_toErase.empty()) {
        auto front = this->_toErase.front();
        *(sf::Color * )(4 * (front.second * SCREEN_X + front.first) + arr) = pixels;
        this->_toErase.pop();
    }
}