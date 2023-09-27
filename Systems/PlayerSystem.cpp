/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.cpp
*/

#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem(const Player &player) : _drawSystem(player.getDrawable(), player.getPosition())
{
    this->_player = player;
}

void PlayerSystem::getInputs(std::unique_ptr<sf::RenderWindow> &window)
{
    sf::Event event;
    while (window->pollEvent(event))
        this->_inputSystem.handleInput(event, window);
}

void PlayerSystem::updateShots(void)
{
    for (int i = 0; i != this->_shots.size(); ++i)
        this->_shots[i].updatePos();
}

void PlayerSystem::drawShots(std::unique_ptr<sf::RenderWindow> &window)
{
    for (int i = 0; i != this->_shots.size(); ++i)
        this->_shots[i].draw(window);
}

void PlayerSystem::createShots(void)
{
    while (this->_inputSystem._inputs.getEvents().front() == Inputs::Events::Shoot) {
        this->_inputSystem._inputs.popEvent();
        Shoot tmpShoot(this->_player.shoot());
        this->_shots.push_back(ShotSystem(ShotEntity(tmpShoot)));
    }
}

void PlayerSystem::updatePos(void)
{
    this->_inputSystem.updatePlayer(this->_player);
}

void PlayerSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_drawSystem.setPosition(this->_player.getPosition());
    this->_drawSystem.draw(window);
}
