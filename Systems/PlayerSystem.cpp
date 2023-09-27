/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.cpp
*/

#include "PlayerSystem.hpp"

void PlayerSystem::setPlayer(const Player &p)
{
    this->_player = p;
    this->_drawSystem = std::make_unique<DrawSystem>(p.getDrawable(), p.getPosition());
}

Player PlayerSystem::getPlayer(void) const
{
    return (this->_player);
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
        this->_shots[i]->updatePos();
}

void PlayerSystem::drawShots(std::unique_ptr<sf::RenderWindow> &window)
{
    for (int i = 0; i != this->_shots.size(); ++i)
        this->_shots[i]->draw(window);
}

void PlayerSystem::createShots(void)
{
    while (!this->_inputSystem._inputs.getEvents().empty() && this->_inputSystem._inputs.getEvents().front() == Inputs::Events::Shoot) {
        this->_inputSystem._inputs.popEvent();
        Shoot tmpShoot(this->_player.shoot());
        this->_shots.push_back(std::make_unique<ShotSystem>(ShotEntity(tmpShoot)));
    }
}

void PlayerSystem::updatePiercingShots(void)
{
    for (int i = 0; i != this->_piercingShots.size(); ++i)
        this->_piercingShots[i]->updatePos();
}

void PlayerSystem::drawPiercingShots(std::unique_ptr<sf::RenderWindow> &window)
{
    for (int i = 0; i != this->_piercingShots.size(); ++i)
        this->_piercingShots[i]->draw(window);
}

void PlayerSystem::createPiercingShots(void)
{
    while (!this->_inputSystem._inputs.getEvents().empty() && this->_inputSystem._inputs.getEvents().front() == Inputs::Events::PiercingShoot) {
        this->_inputSystem._inputs.popEvent();
        Shoot tmpShoot(this->_player.shoot());
        this->_piercingShots.push_back(std::make_unique<PiercingShotSystem>(PiercingShotEntity(tmpShoot)));
    }
}

void PlayerSystem::updatePos(void)
{
    this->_inputSystem.updatePlayer(this->_player);
}

void PlayerSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_drawSystem->setPosition(this->_player.getPosition());
    this->_drawSystem->draw(window);
}
