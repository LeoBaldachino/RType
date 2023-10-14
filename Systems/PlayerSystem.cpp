/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.cpp
*/

#include "PlayerSystem.hpp"

PlayerSystem::PlayerSystem()
{

}

void PlayerSystem::getInputs(Player &p)
{
    // int rE = rand() % 6;
    // this->_inputSystem._inputs.addEvents((Inputs::Events) rE);
    // // sf::Event event;
    // // while (window->pollEvent(event))
    // //     this->_inputSystem.handleInput();
}

void PlayerSystem::createShots(Player &p, Core &core)
{
    while (!p._inputs.getEvents().empty() && p._inputs.getEvents().front() == Inputs::Events::Shoot) {
        p._inputs.popEvent();
        Shoot tmpShoot(p.shoot());
        core.addEntity(std::make_shared<ShotEntity>(tmpShoot, "Assets/shot.png", true), core.getAvailabeIndex());
    }
}

void PlayerSystem::createPiercingShots(Player &p, Core &core)
{
    while (!p._inputs.getEvents().empty() && p._inputs.getEvents().front() == Inputs::Events::PiercingShoot) {
        p._inputs.popEvent();
        Shoot tmpShoot(p.shoot());
        core.addEntity(std::make_shared<PiercingShotEntity>(tmpShoot), core.getAvailabeIndex());
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
        if (p.getLifes() >= 1)
            if (p.removeOneLife())
                std::cout << "One life removed !" << std::endl;
        core.removeEntityLater(entity);
    }
}