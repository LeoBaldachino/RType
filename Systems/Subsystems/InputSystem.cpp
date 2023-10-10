/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** InputSystem.cpp
*/

#include "InputSystem.hpp"

void InputSystem::updatePlayer(Player &player)
{
    if (player._inputs.getEvents().size() == 0)
        return;
    if (player._inputs.getEvents().front() == Inputs::Events::Up) {
        player._inputs.popEvent();
        int add = 0;
        if (player._inputs.getEvents().size() != 0) {
            if (player._inputs.getEvents().front() == Inputs::Left) {
                player._inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (player._inputs.getEvents().front() == Inputs::Right) {
                player._inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() + add, player.getPosition().getY() - (1 * player.getVelocity())));
        return;
    }
    if (player._inputs.getEvents().front() == Inputs::Events::Down) {
        player._inputs.popEvent();
        int add = 0;
        if (player._inputs.getEvents().size() != 0) {
            if (player._inputs.getEvents().front() == Inputs::Left) {
                player._inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (player._inputs.getEvents().front() == Inputs::Right) {
                player._inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() + add, player.getPosition().getY() + (1 * player.getVelocity())));
        return;
    }
    if (player._inputs.getEvents().front() == Inputs::Events::Left) {
        player._inputs.popEvent();
        int add = 0;
        if (player._inputs.getEvents().size() != 0) {
            if (player._inputs.getEvents().front() == Inputs::Up) {
                player._inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (player._inputs.getEvents().front() == Inputs::Down) {
                player._inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() - (1 * player.getVelocity()), player.getPosition().getY() + add));
        return;
    }
    if (player._inputs.getEvents().front() == Inputs::Events::Right) {
        player._inputs.popEvent();
        int add = 0;
        if (player._inputs.getEvents().size() != 0) {
            if (player._inputs.getEvents().front() == Inputs::Up) {
                player._inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (player._inputs.getEvents().front() == Inputs::Down) {
                player._inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() + (1 * player.getVelocity()), player.getPosition().getY() + add));
        return;
    }
}
