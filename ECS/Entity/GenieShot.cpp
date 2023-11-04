/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GenieShot.cpp
*/

#include "GenieShot.hpp"

GenieShot::GenieShot(Position position) :
_frameClock(75),
_size(GENIESHOT_X, GENIESHOT_Y),
_readyMove(MOVE_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(GENIESHOT_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
    this->_originalPos = position;
}

void GenieShot::accept(IVisitor &v, Core &core)
{
    v.visitGenieShot(*this, core);
}

void GenieShot::setPosition(const Position &position)
{
    this->_position = position;
}

Position GenieShot::getPosition() const
{
    return this->_position;
}

void GenieShot::setState(State state)
{
    this->_state = state;
}

State GenieShot::getState() const
{
    return this->_state;
}

void GenieShot::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int GenieShot::getVelocity(void) const
{
    return this->_velocity;
}

void GenieShot::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable GenieShot::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d GenieShot::getSize(void)
{
    return (this->_size);
}

bool GenieShot::isColidingWith(IEntity &entity)
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

bool GenieShot::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void GenieShot::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int GenieShot::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 3 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> GenieShot::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void GenieShot::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer GenieShot::getTempoState(void)
{
    return this->_currentTempoState;
}

Position GenieShot::getOriginalPos(void) const
{
    return (this->_originalPos);
}

void GenieShot::setGoingUp(bool state)
{
    this->_goingUp = state;
}

bool GenieShot::getGoingUp(void) const
{
    return (this->_goingUp);
}
