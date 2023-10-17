/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Tourre.cpp
*/

#include "Tourre.hpp"

Tourre::Tourre(Position position, int velocity, Vector2d moveDirection)
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

void Tourre::accept(IVisitor &v, Core &core)
{
    v.visitTourre(*this, core);
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

bool Tourre::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void Tourre::setHasMoved(bool state)
{
    this->_hasMoved = state;
}
