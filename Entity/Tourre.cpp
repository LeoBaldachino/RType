/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Tourre.cpp
*/

#include "Tourre.hpp"


Tourre::Tourre(Position position, int velocity, Vector2d moveDirection) : _drawable("Assets/tourre.png", 2)
{
    this->_position = position;
    this->_state = State(100);
    this->_velocity = velocity;
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

Shoot Tourre::shoot(const Position &playerPos) const
{   
    AIShoot aiShoot(playerPos, this->_position);
    return aiShoot.shootLogic();
}

void Tourre::accept(IVisitor &v)
{
    v.visitTourre(*this);
}

void Tourre::setPosition(const Position &position)
{
    this->_position = position;
}

Position Tourre::getPosition() const
{
    return this->_position;
}

void Tourre::setState(State state)
{
    this->_state = state;
}

State Tourre::getState() const
{
    return this->_state;
}

void Tourre::setDrawable(Drawable drawable)
{
    this->_drawable = drawable;
}

Drawable Tourre::getDrawable() const
{
    return this->_drawable;
}

void Tourre::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int Tourre::getVelocity(void) const
{
    return this->_velocity;
}

void Tourre::setShootDmg(int shootDmg)
{
    this->_shootDmg = shootDmg;
}

int Tourre::getShootDmg(void) const
{
    return this->_shootDmg;
}

void Tourre::setShootVelocity(int shootVelocity)
{
    this->_shootVelocity = shootVelocity;
}

int Tourre::getShootVelocity(void) const
{
    return this->_shootVelocity;
}

void Tourre::setShootGravity(int shootGravity)
{
    this->_shootGravity = shootGravity;
}

int Tourre::getShootGravity(void) const
{
    return this->_shootGravity;
}

void Tourre::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Tourre::getMoveable(void) const
{
    return (this->_movement);
}

void Tourre::addMessage(RType::Utils::MessageParsed_s &message)
{
    this->_messages.push(message);
}

void Tourre::popMessage(void)
{
    this->_messages.pop();
}
