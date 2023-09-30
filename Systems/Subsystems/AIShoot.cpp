/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** AIShoot.cpp
*/

#include "AIShoot.hpp"

AIShoot::AIShoot(const Position &playerPos, const Position &shooterPos)
{
    this->_playerPos = playerPos;
    this->_shooterPos = shooterPos;
}

void AIShoot::setPlayerPos(const Position &playerPos)
{
    this->_playerPos = playerPos;
}

void AIShoot::setShooterPos(const Position &shooterPos)
{
    this->_shooterPos = shooterPos;
}

void AIShoot::setDmg(const int &dmg)
{
    this->_dmg = dmg;
}

void AIShoot::setVelocity(const int &velocity)
{
    this->_velocity = velocity;
}
void AIShoot::setGravity(const float &gravity)
{
    this->_gravity = gravity;
}

Shoot AIShoot::shootLogic(void)
{
    return (Shoot(Vector2d(this->_shooterPos.getX() - this->_playerPos.getX(),
    this->_shooterPos.getY() - this->_playerPos.getY()), Vector2d(this->_shooterPos.getX(), this->_shooterPos.getY()),
    this->_dmg, this->_velocity, this->_gravity, false));
}
