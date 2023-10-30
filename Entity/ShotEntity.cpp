/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotEntity.cpp
*/

#include "ShotEntity.hpp"

ShotEntity::ShotEntity(Shoot &shoot, std::string spriteFile, bool playerShoot) :
_shoot(shoot),
_size(SHOT_X, SHOT_Y),
_clockMove(MOVE_SHOT),
_frameClock(100),
_currentTempoState(getEntityPositionRange()[3])
{
    this->_playerShoot = playerShoot;
}

Shoot ShotEntity::getShoot(void) const
{
    return (this->_shoot);
}

void ShotEntity::setShoot(const Shoot &shoot)
{
    this->_shoot = shoot;
}

Vector2d ShotEntity::getSize(void)
{
    return (this->_size);
}

bool ShotEntity::isColidingWith(IEntity &entity)
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

Moveable ShotEntity::getMoveable(void) const
{
    return (Moveable(this->_shoot.getOrigin(), this->_shoot.getDirection(), this->_shoot.getVelocity()));
}

void ShotEntity::setMoveable(const Moveable &moveable)
{
    this->_shoot.setOrigin(moveable.getOrigin());
    this->_shoot.setDirection(moveable.getDirection());
    this->_shoot.setVelocity(moveable.getVelocity());
}

Position ShotEntity::getPosition(void) const
{
    return (Position(this->_shoot.getOrigin().x, this->_shoot.getOrigin().y));
}

void ShotEntity::setPosition(const Position &position)
{
    this->_shoot.setOrigin(Vector2d(position.getX(), position.getY()));
}

void ShotEntity::accept(IVisitor &v, Core &core)
{
    v.visitShot(*this, core);
}

bool ShotEntity::getHasMoved(void)
{
    bool tmpHasMoved = this->_hasMoved;
    this->_hasMoved = !this->_hasMoved ? true : false;
    return (tmpHasMoved);
}
void ShotEntity::setHasMoved(bool state)
{
    this->_hasMoved = state;
}

unsigned int ShotEntity::getEntitySpriteFrame()
{
    if (this->_frameClock.clockOk()) {
        ++this->_spriteFrame;
        if (!this->_playerShoot)
            this->_spriteFrame = this->_spriteFrame >= 8 ? 0 : this->_spriteFrame;
    }
    return (this->_spriteFrame);
}

void ShotEntity::setTempoState(ClockTimer state)
{
    this->_currentTempoState = state;
}

ClockTimer ShotEntity::getTempoState(void)
{
    return this->_currentTempoState;
}
