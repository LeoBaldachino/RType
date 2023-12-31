/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Tourre.cpp
*/

#include "Tourre.hpp"

Tourre::Tourre(Position position, int velocity, Vector2d moveDirection) :
_frameClock(125),
_size(TOURRE_X, TOURRE_Y),
_readyShoot(SHOOT_SPEED),
_readyMove(MOVE_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(TOURRE_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
    this->_velocity = velocity;
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
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

void Tourre::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Tourre::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d Tourre::getSize(void)
{
    return (this->_size);
}

bool Tourre::isColidingWith(IEntity &entity)
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

unsigned int Tourre::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 29 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> Tourre::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void Tourre::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer Tourre::getTempoState(void)
{
    return this->_currentTempoState;
}
