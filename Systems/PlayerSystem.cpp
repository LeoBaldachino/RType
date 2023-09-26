/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.cpp
*/

#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem(const Player &player)
{
    this->_player = player;
}

void PlayerSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    DrawSystem tmpDraw(this->_player.getDrawable(), this->_player.getPosition());
    tmpDraw.draw(window);
}
