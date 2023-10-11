/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotSystem.cpp
*/

#include "PiercingShotSystem.hpp"

void PiercingShotSystem::updatePos(PiercingShotEntity &pS)
{
    Shoot tmpShoot = pS.getShoot();
    tmpShoot.setOrigin(Vector2d(tmpShoot.getOrigin().x + tmpShoot.getDirection().x
    * tmpShoot.getVelocity(), tmpShoot.getOrigin().y + tmpShoot.getDirection().y * tmpShoot.getVelocity()));
    pS.setShoot(tmpShoot);
    pS.setHasMoved(true);
}

Position PiercingShotSystem::getPos(PiercingShotEntity &pS) const
{
    return (Position(pS.getShoot().getOrigin().x, pS.getShoot().getOrigin().y));
}
