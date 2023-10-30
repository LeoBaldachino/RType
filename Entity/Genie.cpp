/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Genie.cpp
*/

#include "Genie.hpp"

Genie::Genie(Position position, int velocity, Vector2d moveDirection) :
_frameClock(125),
_size(GENIE_X, GENIE_Y),
_readyShoot(SHOOT_SPEED),
_readyMove(MOVE_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(GENIE_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
    this->_velocity = velocity;
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

// Shoot Genie::shoot(const Position &playerPos) const
// {   
//     AIShoot aiShoot(playerPos, this->_position);
//     return aiShoot.shootLogic();
// }

void Genie::accept(IVisitor &v, Core &core)
{
    v.visitGenie(*this, core);
}

void Genie::setPosition(const Position &position)
{
    this->_position = position;
}

Position Genie::getPosition() const
{
    return this->_position;
}

void Genie::setState(State state)
{
    this->_state = state;
}

State Genie::getState() const
{
    return this->_state;
}

void Genie::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int Genie::getVelocity(void) const
{
    return this->_velocity;
}

// void Genie::setShootDmg(int shootDmg)
// {
//     this->_shootDmg = shootDmg;
// }

// int Genie::getShootDmg(void) const
// {
//     return this->_shootDmg;
// }

// void Genie::setShootVelocity(int shootVelocity)
// {
//     this->_shootVelocity = shootVelocity;
// }

// int Genie::getShootVelocity(void) const
// {
//     return this->_shootVelocity;
// }

// void Genie::setShootGravity(int shootGravity)
// {
//     this->_shootGravity = shootGravity;
// }

// int Genie::getShootGravity(void) const
// {
//     return this->_shootGravity;
// }

void Genie::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Genie::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d Genie::getSize(void)
{
    return (this->_size);
}

bool Genie::isColidingWith(IEntity &entity)
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

bool Genie::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void Genie::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int Genie::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 29 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> Genie::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void Genie::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer Genie::getTempoState(void)
{
    return this->_currentTempoState;
}