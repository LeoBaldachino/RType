/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(Position position, int velocity, Vector2d moveDirection)
{
    this->_position = position;
    this->_state = State(100);
    this->_movement = Moveable(Vector2d(this->_position.getX(), this->_position.getY()), moveDirection, velocity);
}

Shoot Player::shoot() const
{
    Vector2d shootDirection = {1, 0};
    Vector2d playerPos = {this->_position.getX(), this->_position.getY()};


    return Shoot(shootDirection, playerPos, this->_shootDmg, this->_shootVelocity, this->_shootGravity, true);
}
/* Player position methods */

void Player::move(Vector2d direction)
{

}

void Player::setPosition(Position position)
{
    this->_position = position;
}

Position Player::getPosition() const
{
    return this->_position;
}

/* Player Hitbox & State methods */

void Player::setHitbox(Hitbox hitbox)
{
    // this->_hitbox = hitbox;
}

Hitbox Player::getHitbox() const
{
    // return this->_hitbox;
}

void Player::setState(State state)
{
    this->_state = state;
}

State Player::getState() const
{
    return this->_state;
}

/* Player movements methods */

void Player::setMoveable(Moveable moveable)
{
    this->_movement = moveable;
}

Moveable Player::getMoveable() const
{
    return this->_movement;
}
