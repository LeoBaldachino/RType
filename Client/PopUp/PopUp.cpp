/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PopUp
*/

#include "PopUp.hpp"

RType::PopUp::PopUp(const std::string &text, const std::string &font)
{
    this->_font.loadFromFile(font);
    this->_rect.setFillColor(sf::Color::White);
    this->_rect.setOutlineColor(sf::Color::Blue);
    this->_rect.setPosition(sf::Vector2f(760.0, 0.0));
    this->_rect.setSize(sf::Vector2f(400.0, 100.0));
    this->_text.setPosition(sf::Vector2f(760.0, 0.0));
    this->_text.setString(text);
    this->_text.setFillColor(sf::Color::Black);
    this->_text.setFont(this->_font);
    this->_timeout = std::chrono::steady_clock::now();
}

RType::PopUp::~PopUp()
{
}


void RType::PopUp::display(std::unique_ptr<sf::RenderWindow> &window)
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_timeout).count() > POPUP_LAST_TIME)
        return;
    window->draw(this->_rect);
    window->draw(this->_text);
}

void RType::PopUp::setText(const std::string &text)
{
    std::string newText("");
    int cp = 0;
    for (auto it : text) {
        if (cp % 24 == 0)
            newText += '\n';
        newText += it;
        cp++;
    }
    this->_text.setString(newText);
    this->_timeout = std::chrono::steady_clock::now();
}