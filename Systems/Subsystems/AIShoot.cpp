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
    float testX = this->_playerPos.getX() - this->_shooterPos.getX();
    float testY = this->_playerPos.getY() - this->_shooterPos.getY();
    if (std::abs(testX) > std::abs(testY))
        for (; std::abs(testX) >= 5; testX /= 10, testY /= 10);
    else
        for (; std::abs(testY) >= 5; testX /= 10, testY /= 10);
    return (Shoot(Vector2d(testX, testY), Vector2d(this->_shooterPos.getX(), this->_shooterPos.getY()),
    this->_dmg, this->_velocity, this->_gravity, false));
}
