/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Button
*/

#include "Button.hpp"

RType::Button::Button(const std::function<void()>& handler, const std::string &path, const std::string &text, const sf::Vector2f pos, const sf::IntRect rect, int decalHover, const sf::Font &font) :
_handler(handler),
_path(path),
_text(text),
_pos(pos),
_rect(rect),
_decalHover(decalHover),
_font(font)
{
    this->_rectCheck.height = decalHover;
    this->_rectCheck.left = this->_pos.x;
    this->_rectCheck.top = this->_pos.y;
    this->_rectCheck.width = this->_rect.width;
    this->_actPosHover = 0;
    this->_texture.loadFromFile(this->_path);
    this->_sprite.setTexture(this->_texture);
    this->_sprite.setPosition(this->_pos);
    this->_sfText.setFont(this->_font);
    this->_sfText.setString(this->_text);
    this->_sfText.setPosition(this->_pos);
    this->_timeout = std::chrono::steady_clock::now();
}

void RType::Button::checkClicked(const sf::Vector2i &pos)
{
    if (this->_rectCheck.contains(pos)) {
        this->_actPosHover = 2;
        auto clock = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_timeout).count() < 500)
            return;
        this->_timeout = clock;
        this->_handler();
    }
}

void RType::Button::checkHover(const sf::Vector2i &pos)
{
    if (this->_rectCheck.contains(pos)) 
        this->_actPosHover = 1;
    else
        this->_actPosHover = 0;
}

void RType::Button::display(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_rect.top = this->_actPosHover * this->_decalHover;
    this->_sprite.setTextureRect(this->_rect);
    window->draw(this->_sprite);
    window->draw(this->_sfText);
}
