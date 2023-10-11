/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotSystem.cpp
*/

#include "ShotSystem.hpp"

void ShotSystem::updatePos(ShotEntity &s)
{
    Shoot tmpShoot = s.getShoot();
        tmpShoot.setOrigin(Vector2d(tmpShoot.getOrigin().x + tmpShoot.getDirection().x
        * tmpShoot.getVelocity(), tmpShoot.getOrigin().y + tmpShoot.getDirection().y * tmpShoot.getVelocity()));
    s.setShoot(tmpShoot);
    s.setHasMoved(true);
}

Position ShotSystem::getPos(ShotEntity &s) const
{
    return (Position(s.getShoot().getOrigin().x, s.getShoot().getOrigin().y));
}
