/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(Position position) : _drawable("Assets/player.png", 2), _size(PLAYER_X, PLAYER_Y)
{
    this->_position = position;
    this->_state = State(100);
    this->_velocity = 5;
}

Shoot Player::shoot() const
{
    Vector2d shootDirection = {1, 0};
    Vector2d playerPos = {(float) this->_position.getX() + 32, (float) this->_position.getY() + 14};

    return Shoot(shootDirection, playerPos, this->_shootDmg, this->_shootVelocity, this->_shootGravity, true);
}

void Player::accept(IVisitor &v)
{
    v.visitPlayer(*this);
}

void Player::move(Vector2d direction)
{

}

void Player::setPosition(const Position &position)
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

void Player::setMoveable(const Moveable &moveable)
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

Vector2d Player::getSize(void)
{
    return (this->_size);
}

bool Player::isColidingWith(IEntity &entity)
{
    for (int i = entity.getPosition().getX(); i <= entity.getPosition().getX() + entity.getSize().x; i++)
        for (int j = entity.getPosition().getY(); j <= entity.getPosition().getY() + entity.getSize().y; j++)
            if (this->_position.getX() < i &&
                this->_position.getY() < j &&
                this->_position.getY() + this->_size.y >= j &&
                this->_position.getX() + this->_size.x >= i)
                return (true);
    return (false);
}

// const unsigned char Player::returnType(void)
// {
//     return (this->_type);
// }
