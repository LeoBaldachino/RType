/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotSystem.cpp
*/

#include "ShotSystem.hpp"

ShotSystem::ShotSystem(const ShotEntity &shotEntity) : _shotEntity(shotEntity)
{
    this->_drawSystem = std::make_unique<DrawSystem>(shotEntity.getDrawable(), Position(0, 0));
}

void ShotSystem::updatePos(void)
{
    Shoot tmpShoot = this->_shotEntity.getShoot();
    tmpShoot.setOrigin(Vector2d(tmpShoot.getOrigin().x + tmpShoot.getDirection().x
    * tmpShoot.getVelocity(), tmpShoot.getOrigin().y + tmpShoot.getDirection().y * tmpShoot.getVelocity()));
    this->_shotEntity.setShoot(tmpShoot);
}

void ShotSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_drawSystem->setPosition(Position(this->_shotEntity.getShoot().getOrigin().x, this->_shotEntity.getShoot().getOrigin().y));
    this->_drawSystem->draw(window);
}