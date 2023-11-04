/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DragonShot.cpp
*/

#include "DragonShot.hpp"

DragonShot::DragonShot(Position position) :
_frameClock(75),
_size(DRAGONSHOT_X, DRAGONSHOT_Y),
_readyMove(MOVE_SPEED),
_currentTempoState(getEntityPositionRange()[3]),
Health(DRAGONSHOT_HEALTH)
{
    this->_position = position;
    this->_state = State(100);
    this->_originalPos = position;
}

void DragonShot::accept(IVisitor &v, Core &core)
{
    v.visitDragonShot(*this, core);
}

void DragonShot::setPosition(const Position &position)
{
    this->_position = position;
}

Position DragonShot::getPosition() const
{
    return this->_position;
}

void DragonShot::setState(State state)
{
    this->_state = state;
}

State DragonShot::getState() const
{
    return this->_state;
}

void DragonShot::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int DragonShot::getVelocity(void) const
{
    return this->_velocity;
}

void DragonShot::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable DragonShot::getMoveable(void) const
{
    return (this->_movement);
}

Vector2d DragonShot::getSize(void)
{
    return (this->_size);
}

bool DragonShot::isColidingWith(IEntity &entity)
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

bool DragonShot::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void DragonShot::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int DragonShot::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 32 ? 5 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> DragonShot::getEntityPositionRange()
{
    std::vector<float> range = {1080 - 53, 730, 100, 1000};

    return range;
}

void DragonShot::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer DragonShot::getTempoState(void)
{
    return this->_currentTempoState;
}

Position DragonShot::getOriginalPos(void) const
{
    return (this->_originalPos);
}

void DragonShot::setGoingUp(bool state)
{
    this->_goingUp = state;
}

bool DragonShot::getGoingUp(void) const
{
    return (this->_goingUp);
}
