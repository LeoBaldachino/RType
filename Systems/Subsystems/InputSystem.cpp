/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** InputSystem.cpp
*/

#include "InputSystem.hpp"

// void InputSystem::convertMsgToInputs(Player &player)
// {
//     while (!player.isMsgEmpty()) {
//         if (player.getFirstMsg().msgType == 14)
//             this->_inputs.addEvents((Inputs::Events) player.getFirstMsg().getFirstShort());
//         player.popMessage();
//     }
// }

void InputSystem::updatePlayer(Player &player)
{
    if (this->_inputs.getEvents().size() == 0)
        return;
    if (this->_inputs.getEvents().front() == Inputs::Events::Up) {
        this->_inputs.popEvent();
        int add = 0;
        if (this->_inputs.getEvents().size() != 0) {
            if (this->_inputs.getEvents().front() == Inputs::Left) {
                this->_inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (this->_inputs.getEvents().front() == Inputs::Right) {
                this->_inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() + add, player.getPosition().getY() - (1 * player.getVelocity())));
        return;
    }
    if (this->_inputs.getEvents().front() == Inputs::Events::Down) {
        this->_inputs.popEvent();
        int add = 0;
        if (this->_inputs.getEvents().size() != 0) {
            if (this->_inputs.getEvents().front() == Inputs::Left) {
                this->_inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (this->_inputs.getEvents().front() == Inputs::Right) {
                this->_inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() + add, player.getPosition().getY() + (1 * player.getVelocity())));
        return;
    }
    if (this->_inputs.getEvents().front() == Inputs::Events::Left) {
        this->_inputs.popEvent();
        int add = 0;
        if (this->_inputs.getEvents().size() != 0) {
            if (this->_inputs.getEvents().front() == Inputs::Up) {
                this->_inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (this->_inputs.getEvents().front() == Inputs::Down) {
                this->_inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() - (1 * player.getVelocity()), player.getPosition().getY() + add));
        return;
    }
    if (this->_inputs.getEvents().front() == Inputs::Events::Right) {
        this->_inputs.popEvent();
        int add = 0;
        if (this->_inputs.getEvents().size() != 0) {
            if (this->_inputs.getEvents().front() == Inputs::Up) {
                this->_inputs.popEvent();
                add = -1 * player.getVelocity();
            } else if (this->_inputs.getEvents().front() == Inputs::Down) {
                this->_inputs.popEvent();
                add = 1 * player.getVelocity();
            }
        }
        player.setPosition(Position(player.getPosition().getX() + (1 * player.getVelocity()), player.getPosition().getY() + add));
        return;
    }
}
