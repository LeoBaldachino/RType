/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Coin.cpp
*/

#include "Coin.hpp"

Coin::Coin(Position position) :
_frameClock(100),
_size(COIN_X, COIN_Y),
_currentTempoState(getEntityPositionRange()[3]),
_readyMove(MOVE_SPEED)
{
    this->_position = position;
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), Vector2d(-1, 0), this->_velocity);
}

void Coin::accept(IVisitor &v, Core &core)
{
    v.visitCoin(*this, core);
}

void Coin::setMoveable(const Moveable &moveable)
{
    this->_movement = moveable;
}

Moveable Coin::getMoveable(void) const
{
    return (this->_movement);
}

void Coin::setPosition(const Position &position)
{
    this->_position = position;
}

Position Coin::getPosition(void) const
{
    return (this->_position);
}

Vector2d Coin::getSize(void)
{
    return (this->_size);
}

bool Coin::getHasMoved(void)
{
    return (this->_hasMoved);
}

void Coin::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int Coin::getEntitySpriteFrame(void)
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 16 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

std::vector<float> Coin::getEntityPositionRange()
{
    std::vector<float> range = {0, 0, 0, 0};
    return (range);
}

void Coin::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer Coin::getTempoState()
{
    return (this->_currentTempoState);
}
