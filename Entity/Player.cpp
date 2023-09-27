/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(Position position) : _drawable("Assets/player.png", 2)
{
    this->_position = position;
    this->_state = State(100);
    this->_velocity = 15;
}

Shoot Player::shoot() const
{
    Vector2d shootDirection = {1, 0};
    Vector2d playerPos = {this->_position.getX() + 20, this->_position.getY() + 15};

    return Shoot(shootDirection, playerPos, this->_shootDmg, this->_shootVelocity, this->_shootGravity, true);
}

void Player::accept(IVisitor &v, Player &p, std::unique_ptr<sf::RenderWindow> &window)
{
    v.visitPlayer(*this, window);
}

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

// void Player::setHitbox(Hitbox hitbox)
// {
//     // this->_hitbox = hitbox;
// }

// Hitbox Player::getHitbox() const
// {
//     // return this->_hitbox;
// }

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

/* Player draw methods */

void Player::setDrawable(Drawable drawable)
{
    this->_drawable = drawable;
}

Drawable Player::getDrawable() const
{
    return this->_drawable;
}

/* Player velocity methods */

void Player::setVelocity(int velocity)
{
    this->_velocity = velocity;
}

int Player::getVelocity(void) const
{
    return (this->_velocity);
}

// const unsigned char Player::returnType(void)
// {
//     return (this->_type);
// }
