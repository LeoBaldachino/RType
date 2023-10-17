/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bydos.cpp
*/

#include "Bydos.hpp"

Bydos::Bydos(Position position, int velocity, Vector2d moveDirection) : 
_size(BYDOS_X, BYDOS_Y),
_readyShoot(SHOOT_SPEED),
_readyMove(MOVE_SPEED),
_frameClock(100),
Health(BYDOS_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
    this->_velocity = velocity;
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

Shoot Bydos::shoot(const Position &playerPos) const
{
    AIShoot aiShoot(playerPos, this->_position);
    return aiShoot.shootLogic();
}

void Bydos::accept(IVisitor &v, Core &core)
{
    v.visitBydos(*this, core);
}

void Bydos::setPosition(const Position &position)
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

void Bydos::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Bydos::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d Bydos::getSize(void)
{
    return (this->_size);
}

bool Bydos::isColidingWith(IEntity &entity)
{
    for (int i = entity.getPosition().getX(); i <= entity.getPosition().getX() + entity.getSize().x; i++)
        for (int j = entity.getPosition().getY(); j <= entity.getPosition().getY() + entity.getSize().y; j++)
            if (this->_position.getX() < i &&
                this->_position.getY() < j &&
                this->_position.getY() + this->_size.y >= j &&
                this->_position.getX() + this->_size.x >= i)
                return (true);
    return (false);
}

bool Bydos::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void Bydos::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int Bydos::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 5 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}
