/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.cpp
*/

#include "PiercingShotEntity.hpp"

PiercingShotEntity::PiercingShotEntity(Shoot &shoot) : _drawable("Assets/piercingShot.png", 1), _shoot(shoot)
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

Drawable PiercingShotEntity::getDrawable(void) const
{
    return (this->_drawable);
}

void PiercingShotEntity::setDrawable(const Drawable &drawable)
{
    this->_drawable = drawable;
}
