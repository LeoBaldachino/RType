/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Button
*/

#include "Button.hpp"

RType::Button::Button(const std::function<void()>& handler, const std::string &path, const std::string &text, const sf::Vector2f pos, const sf::IntRect rect, int decalHover) :
_handler(handler),
_path(path),
_text(text),
_pos(pos),
_rect(rect),
_decalHover(decalHover)
{
    this->_actPosHover = 0;
    this->_texture.loadFromFile(this->_path);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(this->_pos);
}

RType::Button::~Button()
{
}


void RType::Button::checkClicked(const sf::Vector2i &pos)
{
    sf::IntRect rect;
    rect.width = 1;
    rect.height = 1;
    rect.left = pos.x;
    rect.left = pos.y;
    if (this->_rect.intersects(rect)) {
        this->_actPosHover = 2;
        this->_handler();
    }
}

void RType::Button::checkHover(const sf::Vector2i &pos)
{
    sf::IntRect rect;
    rect.width = 1;
    rect.height = 1;
    rect.left = pos.x;
    rect.left = pos.y;
    if (this->_rect.intersects(rect))
        if (this->_actPosHover != 2)
            this->_actPosHover = 1;
    else
        this->_actPosHover = 0;
}

void RType::Button::display(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_rect.top = this->_actPosHover * this->_decalHover;
    this->_sprite.setTextureRect(this->_rect);
    window->draw(this->_sprite);
}
