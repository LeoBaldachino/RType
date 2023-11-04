/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GenieShotSystem.cpp
*/

#include "GenieShotSystem.hpp"

void GenieShotSystem::updatePos(GenieShot &gS)
{
    if (!gS.readyToMove())
        return;
    gS.setPosition(Position(gS.getPosition().getX() - 1, gS.getPosition().getY()));
    if (gS.getPosition().getY() >= gS.getOriginalPos().getY() + 200)
        gS.setGoingUp(true);
    if (gS.getPosition().getY() < gS.getOriginalPos().getY() - 200)
        gS.setGoingUp(false);
    if (gS.getPosition().getY() == 0)
        gS.setGoingUp(false);
    if (gS.getPosition().getY() == gS.getPosition().getHeight())
        gS.setGoingUp(true);
    if (gS.getGoingUp())
        gS.setPosition(Position(gS.getPosition().getX(), gS.getPosition().getY() - 1));
    if (!gS.getGoingUp() && gS.getPosition().getY() < gS.getPosition().getHeight())
        gS.setPosition(Position(gS.getPosition().getX(), gS.getPosition().getY() + 1));
    gS.setHasMoved(true);
}

void GenieShotSystem::checkCollision(GenieShot &gS, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(gS, entity)) {
        if (gS.getLifes() >= 1)
            gS.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}
