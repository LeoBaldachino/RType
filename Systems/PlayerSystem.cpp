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
}

Player PlayerSystem::getPlayer(void) const
{
    return (this->_player);
}

void PlayerSystem::getInputs()
{
    int rE = rand() % 6;
    this->_inputSystem._inputs.addEvents((Inputs::Events) rE);
    // // sf::Event event;
    // // while (window->pollEvent(event))
    // //     this->_inputSystem.handleInput();
}

// void PlayerSystem::clearShots(void)
// {
//     for (auto& i: this->_shots) {
//         if (i == NULL || i == nullptr)
//             continue;
//         if (i->getPos().getX() >= this->_player.getPosition().getWidth()
//         || i->getPos().getY() >= this->_player.getPosition().getHeight())
//             this->_shots.erase(std::find(std::begin(this->_shots), std::end(this->_shots), i));
//     }
// }

void PlayerSystem::createShots(Core &core)
{
    while (!this->_inputSystem._inputs.getEvents().empty() && this->_inputSystem._inputs.getEvents().front() == Inputs::Events::Shoot) {
        this->_inputSystem._inputs.popEvent();
        Shoot tmpShoot(this->_player.shoot());
        core.addEntity(std::make_shared<ShotEntity>(tmpShoot), core.getAvailabeIndex());
    }
}

void PlayerSystem::createPiercingShots(Core &core)
{
    while (!this->_inputSystem._inputs.getEvents().empty() && this->_inputSystem._inputs.getEvents().front() == Inputs::Events::PiercingShoot) {
        this->_inputSystem._inputs.popEvent();
        Shoot tmpShoot(this->_player.shoot());
        core.addEntity(std::make_shared<PiercingShotEntity>(tmpShoot), core.getAvailabeIndex());
    }
}

void PlayerSystem::updatePos(void)
{
    this->_inputSystem.updatePlayer(this->_player);
    Position tmpPosition(this->_player.getPosition());
    if (this->_player.getPosition().getX() < 0)
        tmpPosition.setX(0);
    if (this->_player.getPosition().getY() < 0)
        tmpPosition.setY(0);
    if (this->_player.getPosition().getX() > this->_player.getPosition().getWidth() - 64)
        tmpPosition.setX(this->_player.getPosition().getWidth() - 64);
    if (this->_player.getPosition().getY() > this->_player.getPosition().getHeight() - 28)
        tmpPosition.setY(this->_player.getPosition().getHeight() - 28);
    this->_player.setPosition(tmpPosition);
}
