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
    this->_list.addButtons([this]{std::cout<< "mod" <<std::endl;this->_exited = true; std::cout << "endmod" << std::endl;}, "../Assets/buttonTest.png", "Start", sf::Vector2f(1035.0, 400.0), sf::IntRect(0, 0, 150, 100), 100, 0);
    this->_list.addButtons([this]{std::exit(0);}, "../Assets/buttonTest.png", "Quit", sf::Vector2f(1035.0, 700.0), sf::IntRect(0, 0, 150, 100), 100, 1);
}

RType::BaseMenu::~BaseMenu()
{
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