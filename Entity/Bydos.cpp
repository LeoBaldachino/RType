/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bydos.cpp
*/

#include "Bydos.hpp"

Bydos::Bydos(Position position, int velocity, Vector2d moveDirection) : _drawable("Assets/player.png", 2)
{
    this->_position = position;
    this->_state = State(100);
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

Shoot Bydos::shoot(const Position &playerPos) const
{   
    AIShoot aiShoot(playerPos, this->_position);
    return aiShoot.shootLogic();
}

void Bydos::accept(IVisitor &v, std::unique_ptr<sf::RenderWindow> &window)
{
    v.visitBydos(*this, window);
}

void Bydos::setPosition(Position position)
{
    this->_position = position;
}

Position Bydos::getPosition() const
{
    return this->_position;
}

void Bydos::setState(State state)
{
    this->_state = state;
}

State Bydos::getState() const
{
    return this->_state;
}

void Bydos::setDrawable(Drawable drawable)
{
    this->_drawable = drawable;
}

Drawable Bydos::getDrawable() const
{
    return this->_drawable;
}

void Bydos::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int Bydos::getVelocity(void) const
{
    return this->_velocity;
}

void Bydos::setShootDmg(int shootDmg)
{
    this->_shootDmg = shootDmg;
}

int Bydos::getShootDmg(void) const
{
    return this->_shootDmg;
}

void Bydos::setShootVelocity(int shootVelocity)
{
    this->_shootVelocity = shootVelocity;
}

int Bydos::getShootVelocity(void) const
{
    return this->_shootVelocity;
}

void Bydos::setShootGravity(int shootGravity)
{
    this->_shootGravity = shootGravity;
}

int Bydos::getShootGravity(void) const
{
    return this->_shootGravity;
}

