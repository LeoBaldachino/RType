/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.cpp
*/

#include "PlayerSystem.hpp"

void PlayerSystem::createShots(Player &p, Core &core)
{
    Shoot tmpShoot(p.shoot());
    while (!p._inputs->isEmpty()) {
        if (p._inputs->getLastEvent() == Inputs::Events::PiercingShoot)
            core.addEntity(std::make_shared<PiercingShotEntity>(tmpShoot), core.getAvailabeIndex());
        else if (p._inputs->getLastEvent() == Inputs::Events::Shoot)
            core.addEntity(std::make_shared<ShotEntity>(tmpShoot, RType::playerShoot, true), core.getAvailabeIndex());
        p._inputs->popEvent();
    }
}

void PlayerSystem::updatePos(Player &p)
{
    Position tmpHasMoved(p.getPosition());
    this->_inputSystem.updatePlayer(p);
    Position tmpPosition(p.getPosition());
    if (p.getPosition().getX() < 0)
        tmpPosition.setX(0);
    if (p.getPosition().getY() < 0)
        tmpPosition.setY(0);
    if (p.getPosition().getX() > p.getPosition().getWidth() - 64)
        tmpPosition.setX(p.getPosition().getWidth() - 64);
    if (p.getPosition().getY() > p.getPosition().getHeight() - 28)
        tmpPosition.setY(p.getPosition().getHeight() - 28);
    p.setPosition(tmpPosition);
    if (tmpHasMoved.getX() != p.getPosition().getX() || tmpHasMoved.getY() != p.getPosition().getY())
        p.setHasMoved(true);
}

void PlayerSystem::checkCollision(Player &p, IEntity &entity, Core &core)
{
    if (this->_hitBoxSystem.entityIntersect(p, entity)) {
        if (entity.getEntityType() == RType::coin)
            p.addLife();
        if (entity.getEntityType() != RType::coin && p.getLifes() >= 1)
            p.removeOneLife();
        if (entity.getEntityType() != RType::genie && entity.getEntityType() != RType::dragon && entity.getEntityType() != RType::mermaid)
            core.removeEntityLater(entity);
    }
}
