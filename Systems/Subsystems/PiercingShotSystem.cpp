/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotSystem.cpp
*/

#include "PiercingShotSystem.hpp"

PiercingShotSystem::PiercingShotSystem(const PiercingShotEntity &piercingShotEntity) : _piercingShotEntity(piercingShotEntity), _drawSystem(piercingShotEntity.getDrawable(), Position(0, 0))
{
}

void PiercingShotSystem::updatePos(void)
{
    Shoot tmpShoot = this->_piercingShotEntity.getShoot();
    tmpShoot.setOrigin(Vector2d(tmpShoot.getOrigin().x + tmpShoot.getDirection().x
    * tmpShoot.getVelocity(), tmpShoot.getOrigin().y + tmpShoot.getDirection().y * tmpShoot.getVelocity()));
    this->_piercingShotEntity.setShoot(tmpShoot);
}

void PiercingShotSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_drawSystem.setPosition(Position(this->_piercingShotEntity.getShoot().getOrigin().x, this->_piercingShotEntity.getShoot().getOrigin().y));
    this->_drawSystem.draw(window);
}
