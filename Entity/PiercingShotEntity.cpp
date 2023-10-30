/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.cpp
*/

#include "PiercingShotEntity.hpp"

PiercingShotEntity::PiercingShotEntity(Shoot &shoot) :
_shoot(shoot),
_size(PIERCING_SHOT_X, PIERCING_SHOT_Y),
_frameClock(100),
_currentTempoState(getEntityPositionRange()[3])
{
}

Shoot PiercingShotEntity::getShoot(void) const
{
    return (this->_shoot);
}

void PiercingShotEntity::setShoot(const Shoot &shoot)
{
    this->_shoot = shoot;
}

Vector2d PiercingShotEntity::getSize(void)
{
    return (this->_size);
}

bool PiercingShotEntity::isColidingWith(IEntity &entity)
{
    for (int i = entity.getPosition().getX(); i <= entity.getPosition().getX() + entity.getSize().x; i++)
        for (int j = entity.getPosition().getY(); j <= entity.getPosition().getY() + entity.getSize().y; j++)
            if (this->_shoot.getDirection().x < i &&
                this->_shoot.getDirection().y < j &&
                this->_shoot.getDirection().y + this->_size.y >= j &&
                this->_shoot.getDirection().x + this->_size.x >= i)
                return (true);
    return (false);
}

Moveable PiercingShotEntity::getMoveable(void) const
{
    return (Moveable(this->_shoot.getOrigin(), this->_shoot.getDirection(), this->_shoot.getVelocity()));
}

void PiercingShotEntity::setMoveable(const Moveable &moveable)
{
    this->_shoot.setOrigin(moveable.getOrigin());
    this->_shoot.setDirection(moveable.getDirection());
    this->_shoot.setVelocity(moveable.getVelocity());
}

Position PiercingShotEntity::getPosition(void) const
{
    return (Position(this->_shoot.getOrigin().x, this->_shoot.getOrigin().y));
}

void PiercingShotEntity::setPosition(const Position &position)
{
    this->_shoot.setOrigin(Vector2d(position.getX(), position.getY()));
}

void PiercingShotEntity::accept(IVisitor &v, Core &core)
{
    v.visitPiercingShot(*this, core);
}

bool PiercingShotEntity::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void PiercingShotEntity::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int PiercingShotEntity::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        this->_spriteFrame = this->_spriteFrame >= 4 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

void PiercingShotEntity::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer PiercingShotEntity::getTempoState(void)
{
    return this->_currentTempoState;
}
