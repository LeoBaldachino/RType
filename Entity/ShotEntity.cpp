/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotEntity.cpp
*/

#include "ShotEntity.hpp"



ShotEntity::ShotEntity(Shoot &shoot) : _drawable("./Assets/shot.png", 1), _shoot(shoot), _size(SHOT_X, SHOT_Y)
{
}

Shoot ShotEntity::getShoot(void) const
{
    return (this->_shoot);
}

void ShotEntity::setShoot(const Shoot &shoot)
{
    this->_shoot = shoot;
}

Drawable ShotEntity::getDrawable(void) const
{
    return (this->_drawable);
}

void ShotEntity::setDrawable(const Drawable &drawable)
{
    this->_drawable = drawable;
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
