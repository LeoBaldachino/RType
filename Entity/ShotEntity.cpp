/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotEntity.cpp
*/

#include "ShotEntity.hpp"

ShotEntity::ShotEntity(Shoot &shoot) : _drawable("./Assets/shot.png", 1), _shoot(shoot)
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
