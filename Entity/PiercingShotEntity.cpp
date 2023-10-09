/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.cpp
*/

#include "PiercingShotEntity.hpp"

PiercingShotEntity::PiercingShotEntity(Shoot &shoot) : _drawable("Assets/piercingShot.png", 1), _shoot(shoot), _size(PIERCING_SHOT_X, PIERCING_SHOT_Y)
{
}

Shoot PiercingShotEntity::getShoot(void) const
{
    return (this->_shoot);
}

void PiercingShotEntity::setShoot(const Shoot &shoot)
{
    this->_shoot = shoot;
}

Drawable PiercingShotEntity::getDrawable(void) const
{
    return (this->_drawable);
}

void PiercingShotEntity::setDrawable(const Drawable &drawable)
{
    this->_drawable = drawable;
}

Vector2d PiercingShotEntity::getSize(void)
{
    return (this->_size);
}

bool PiercingShotEntity::isColidingWith(IEntity &entity)
{
    for (int i = entity.getPosition().getX(); i <= entity.getPosition().getX() + entity.getSize().x; i++)
        for (int j = entity.getPosition().getY(); j <= entity.getPosition().getY() + entity.getSize().y; j++)
            if (this->_shoot.getDirection().x < i &&
                this->_shoot.getDirection().y < j &&
                this->_shoot.getDirection().y + this->_size.y >= j &&
                this->_shoot.getDirection().x + this->_size.x >= i)
                return (true);
    return (false);
}

Moveable PiercingShotEntity::getMoveable(void) const
{
    return (Moveable(this->_shoot.getOrigin(), this->_shoot.getDirection(), this->_shoot.getVelocity()));
}

void PiercingShotEntity::setMoveable(const Moveable &moveable)
{
    this->_shoot.setOrigin(moveable.getOrigin());
    this->_shoot.setDirection(moveable.getDirection());
    this->_shoot.setVelocity(moveable.getVelocity());
}

Position PiercingShotEntity::getPosition(void) const
{
    return (Position(this->_shoot.getOrigin().x, this->_shoot.getOrigin().y));
}

void PiercingShotEntity::setPosition(const Position &position)
{
    this->_shoot.setOrigin(Vector2d(position.getX(), position.getY()));
}

void PiercingShotEntity::drawEntity(std::unique_ptr<sf::RenderWindow> &window)
{
    sf::Sprite sprite = this->_drawable.getSprite();
    sprite.setPosition(this->_shoot.getOrigin().x, this->_shoot.getOrigin().y);
    window->draw(sprite);
}

void PiercingShotEntity::accept(IVisitor &v, Core &core)
{
    v.visitPiercingShot(*this, core);
}
