/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Mermaid.cpp
*/

#include "Mermaid.hpp"

Mermaid::Mermaid(Position position) :
_frameClock(75),
_size(MERMAID_X, MERMAID_Y),
_readyShoot(MERMAIDSHOOT_SPEED),
_readyMove(MOVE_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(MERMAID_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
}

void Mermaid::accept(IVisitor &v, Core &core)
{
    v.visitMermaid(*this, core);
}

void Mermaid::setPosition(const Position &position)
{
    this->_position = position;
}

Position Mermaid::getPosition() const
{
    return this->_position;
}

void Mermaid::setState(State state)
{
    this->_state = state;
}

State Mermaid::getState() const
{
    return this->_state;
}

void Mermaid::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int Mermaid::getVelocity(void) const
{
    return this->_velocity;
}

void Mermaid::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Mermaid::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d Mermaid::getSize(void)
{
    return (this->_size);
}

bool Mermaid::isColidingWith(IEntity &entity)
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

bool Mermaid::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void Mermaid::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int Mermaid::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 20 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> Mermaid::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void Mermaid::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer Mermaid::getTempoState(void)
{
    return this->_currentTempoState;
}

bool Mermaid::getGoingUp(void) const
{
    return (this->_goingUp);
}

void Mermaid::setGoingUp(bool state)
{
    this->_goingUp = state;
}
