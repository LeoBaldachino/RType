/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BaseMenu
*/

#include "BaseMenu.hpp"

RType::BaseMenu::BaseMenu() :
_list("../Assets/insanibu.ttf")
{
    this->_exited = false;
    this->_list.addButtons([this]{this->_exited = true;}, "../Assets/Start_Btn.png", "", sf::Vector2f(885.0, 400.0), sf::IntRect(0, 0, 200, 200), 200, 0);
    this->_list.addButtons([this]{std::exit(0);}, "../Assets/buttonTest.png", "Quit", sf::Vector2f(885.0, 700.0), sf::IntRect(0, 0, 150, 100), 100, 1);
}

void RType::BaseMenu::display(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_list.displayButtons(window);
}


void RType::BaseMenu::hoverButtons(const sf::Vector2i &mousePos)
{
    this->_list.hoverButtons(mousePos);
}

void RType::BaseMenu::clickedButtons(const sf::Vector2i &mousePos)
{
    this->_list.clickButtons(mousePos);
}
