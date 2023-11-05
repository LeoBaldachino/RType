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
    this->_font.loadFromFile("Assets/insanibu.ttf");
    this->_text.setPosition(pos);
    this->_text.setFont(this->_font);
    this->_score = 0;
    this->_serverIp = "";
    this->_serverPort = 0;
}

void RType::Hud::setServerDetails(const std::string &serverIp, int serverPort)
{
    this->_serverIp = serverIp;
    this->_serverPort = serverPort;
}

void RType::Hud::display(std::unique_ptr<sf::RenderWindow> &toDraw)
{
    std::string score = "Score : " + std::to_string(static_cast<int>(this->_score));
    this->_text.setString(score);
    this->_text.setPosition(this->_pos);
    toDraw->draw(this->_text);
    sf::Vector2f newPos(this->_pos);
    newPos.y += 50;
    this->_text.setPosition(newPos);
    this->_text.setString(this->_serverIp);
    toDraw->draw(this->_text);
    newPos.y += 50;
    this->_text.setPosition(newPos);
    this->_text.setString(std::to_string(this->_serverPort));
    toDraw->draw(this->_text);
}
