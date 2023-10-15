/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** InputSystem.cpp
*/

#include "InputSystem.hpp"

void InputSystem::updatePlayer(Player &player)
{
    int y = 0;
    int x = 0;
    int veloc = player.getVelocity();
    std::queue<Inputs::Events> newInputs;
    while (!player._inputs->isEmpty()) {
        switch (player._inputs->getLastEvent())
        {
            case Inputs::Events::Up:
                y += -1 * veloc;
                break;
            case Inputs::Events::Down:
                y += 1 * veloc;
                break;
            case Inputs::Events::Left:
                x += -1 * veloc;
                break;
            case Inputs::Events::Right:
                x += 1 * veloc;
                break;
            case Inputs::Events::PiercingShoot :
                newInputs.push(Inputs::Events::PiercingShoot);
                break;
            case Inputs::Events::Shoot :
                newInputs.push(Inputs::Events::Shoot);
                break;
        }
        player._inputs->popEvent();
    }
    player.setPosition(Position(player.getPosition().getX() + x, player.getPosition().getY() + y));
    player._inputs->setInput(newInputs);
}
