/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ButtonList
*/

#include "ButtonList.hpp"

RType::ButtonList::ButtonList(const std::string &fontFile)
{
    this->_buttonsFont.loadFromFile(fontFile);
}

RType::ButtonList::~ButtonList()
{
}


void RType::ButtonList::addButtons(const std::function<void()>& handler, const std::string &path, const std::string &text, const sf::Vector2f pos, const sf::IntRect rect, int decalHover, unsigned int id)
{
    auto it = this->_buttons.find(id);
    if (it != this->_buttons.end())
        throw std::invalid_argument("A button already exists with this id :" + id);
    this->_buttons.insert({id, std::make_unique<Button>(handler, path, text, pos, rect, decalHover, this->_buttonsFont)});
}

void RType::ButtonList::removeButton(unsigned int id)
{
    auto it = this->_buttons.find(id);
    if (it == this->_buttons.end())
        throw std::invalid_argument("No buttons exists with this id :" + id);
    this->_buttons.erase(it);
}

void RType::ButtonList::displayButtons(std::unique_ptr<sf::RenderWindow> &window)
{
    for (auto &it : this->_buttons)
        it.second->display(window);
}

void RType::ButtonList::hoverButtons(const sf::Vector2i &mousePos)
{
    for (auto &it : this->_buttons)
        it.second->checkHover(mousePos);
}

void RType::ButtonList::clickButtons(const sf::Vector2i &mousePos)
{
    for (auto &it : this->_buttons)
        it.second->checkClicked(mousePos);
}