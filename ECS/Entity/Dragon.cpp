/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Dragon.cpp
*/

#include "Dragon.hpp"

Dragon::Dragon(Position position) :
_frameClock(75),
_size(DRAGON_X, DRAGON_Y),
_readyShoot(DRAGONSHOOT_SPEED),
_readyMove(MOVE_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(DRAGON_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
}

void Dragon::accept(IVisitor &v, Core &core)
{
    v.visitDragon(*this, core);
}

void Dragon::setPosition(const Position &position)
{
    this->_position = position;
}

Position Dragon::getPosition() const
{
    return this->_position;
}

void Dragon::setState(State state)
{
    this->_state = state;
}

State Dragon::getState() const
{
    return this->_state;
}

void Dragon::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int Dragon::getVelocity(void) const
{
    return this->_velocity;
}

void Dragon::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Dragon::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d Dragon::getSize(void)
{
    return (this->_size);
}

bool Dragon::isColidingWith(IEntity &entity)
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

bool Dragon::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void Dragon::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int Dragon::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 16 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> Dragon::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void Dragon::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer Dragon::getTempoState(void)
{
    return this->_currentTempoState;
}

bool Dragon::getGoingUp(void) const
{
    return (this->_goingUp);
}

void Dragon::setGoingUp(bool state)
{
    this->_goingUp = state;
}
