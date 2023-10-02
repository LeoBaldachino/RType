/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BydosSystem.cpp
*/

#include "BydosSystem.hpp"

void BydosSystem::draw(std::unique_ptr<sf::RenderWindow> &window)
{
    this->_drawSystem->setPosition(this->_bydos.getPosition());
    this->_drawSystem->draw(window);
}

void BydosSystem::setBydos(const Bydos &b)
{
    this->_bydos = b;
    this->_drawSystem = std::make_unique<DrawSystem>(b.getDrawable(), b.getPosition());
}

Bydos BydosSystem::getBydos(void) const
{
    return (this->_bydos);
}

void BydosSystem::updatePos(void)
{
    this->_movementSystem.updatePosition(this->_bydos);
}

void BydosSystem::updateShots(void)
{
    for (int i = 0; i != this->_shots.size(); ++i)
        this->_shots[i]->updatePos();
}

void BydosSystem::drawShots(std::unique_ptr<sf::RenderWindow> &window)
{
    for (int i = 0; i != this->_shots.size(); ++i)
        this->_shots[i]->draw(window, "Assets/enemyShot.png");
}

void BydosSystem::createShots(const Player &player)
{
    Shoot tmpShoot(this->_bydos.shoot(player.getPosition()));
    this->_shots.push_back(std::make_unique<ShotSystem>(ShotEntity(tmpShoot)));
}

void BydosSystem::clearShots(void)
{
    for (auto& i: this->_shots) {
        if (i == NULL || i == nullptr)
            continue;
        if (i->getPos().getX() <= 0 || i->getPos().getY() <= 0
        || i->getPos().getX() >= this->_bydos.getPosition().getWidth()
        || i->getPos().getY() >= this->_bydos.getPosition().getHeight())
            this->_shots.erase(std::find(std::begin(this->_shots), std::end(this->_shots), i));
    }
}
