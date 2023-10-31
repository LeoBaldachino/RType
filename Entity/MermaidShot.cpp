/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MermaidShot.cpp
*/

#include "MermaidShot.hpp"

MermaidShot::MermaidShot(Position position) :
_frameClock(75),
_size(MERMAIDSHOT_X, MERMAIDSHOT_Y),
_readyMove(MERMAIDSHOT_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(MERMAIDSHOT_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
    this->_originalPos = position;
}

void MermaidShot::accept(IVisitor &v, Core &core)
{
    v.visitMermaidShot(*this, core);
}

void MermaidShot::setPosition(const Position &position)
{
    this->_position = position;
}

Position MermaidShot::getPosition() const
{
    return this->_position;
}

void MermaidShot::setState(State state)
{
    this->_state = state;
}

State MermaidShot::getState() const
{
    return this->_state;
}

void MermaidShot::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int MermaidShot::getVelocity(void) const
{
    return this->_velocity;
}

void MermaidShot::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable MermaidShot::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d MermaidShot::getSize(void)
{
    return (this->_size);
}

bool MermaidShot::isColidingWith(IEntity &entity)
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

bool MermaidShot::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void MermaidShot::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int MermaidShot::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 32 ? 5 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> MermaidShot::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void MermaidShot::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer MermaidShot::getTempoState(void)
{
    return this->_currentTempoState;
}

Position MermaidShot::getOriginalPos(void) const
{
    return (this->_originalPos);
}

void MermaidShot::setGoingUp(bool state)
{
    this->_goingUp = state;
}

bool MermaidShot::getGoingUp(void) const
{
    return (this->_goingUp);
}
