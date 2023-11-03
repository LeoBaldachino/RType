/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Hud
*/

#include "Hud.hpp"

RType::Hud::Hud(const sf::Vector2f &pos)
{
    this->_pos = pos;
    this->_font.loadFromFile("../Assets/insanibu.ttf");
    this->_text.setPosition(pos);
    this->_text.setFont(this->_font);
    this->_score = 0;
}

RType::Hud::~Hud()
{
}

void RType::Hud::display(std::unique_ptr<sf::RenderWindow> &toDraw)
{
    std::string score = "Score : " + std::to_string(static_cast<int>(this->_score));
    this->_text.setString(score);
    toDraw->draw(this->_text);
}
