/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MermaidSystem.cpp
*/

#include "MermaidSystem.hpp"

void MermaidSystem::updatePos(Mermaid &t)
{
    if (!t.readyToMove())
        return;
    if (t.getPosition().getX() > 1920 - 400)
        t.setPosition(Position(t.getPosition().getX() - 1, t.getPosition().getY()));
    else {
        if (t.getGoingUp()) {
            t.setPosition(Position(t.getPosition().getX() - 1, t.getPosition().getY()));
            if (t.getPosition().getX() < 1100)
                t.setGoingUp(false);
        } else {
            t.setPosition(Position(t.getPosition().getX() + 1, t.getPosition().getY()));
            if (t.getPosition().getX() > 1400)
                t.setGoingUp(true);
        }
    }
    t.setHasMoved(true);
}

void MermaidSystem::checkCollision(Mermaid &t, IEntity &entity, Core &core, bool isTouching)
{
    if (this->_hitBoxSystem.entityIntersect(t, entity)) {
        if (t.getLifes() >= 1)
            t.removeOneLife();
        if (!isTouching)
            core.removeEntityLater(entity);
    }
}

// void MermaidSystem::shot(Mermaid &t, Core &core)
// {
//     if (!t.readyToShoot())
//         return;
//     MermaidShot tmpMermaidShot(t.getPosition());
//     core.addEntity(std::make_shared<MermaidShot>(tmpMermaidShot), core.getAvailabeIndex());
// }
