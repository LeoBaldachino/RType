/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DrawSystem.cpp
*/

#include "DrawSystem.hpp"

DrawSystem::DrawSystem(const Drawable &drawable, const Position &position)
{
    this->_drawable = drawable;
    this->_position = position;
}

void DrawSystem::setDrawable(const Drawable &drawable)
{
    this->_drawable = drawable;
}

void DrawSystem::setPosition(const Position &position)
{
    this->_position = position;
}

void DrawSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    sf::Sprite tmpSprite = this->_drawable.getSprite();
    tmpSprite.setPosition(sf::Vector2f(this->_position.getX(), this->_position.getY()));
    window->draw(tmpSprite);
}
