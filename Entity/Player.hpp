/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Player.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/Shoot.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
// #include "../Components/Hitbox.hpp"
#include "../Components/Moveable.hpp"
#include "../Components/Drawable.hpp"

class Player : public IEntity {
    public:
        Player(Position position);
        Player() {};
        ~Player() {};
        void accept(IVisitor &v, Player &p ,std::unique_ptr<sf::RenderWindow> &window);

        Shoot shoot() const;

        void move(Vector2d direction);

        void setPosition(Position position);
        Position getPosition() const;

        // void setHitbox(Hitbox hitbox);
        // Hitbox getHitbox() const;

        void setState(State state);
        State getState() const;

        void setMoveable(Moveable moveable);
        Moveable getMoveable() const;

        void setDrawable(Drawable drawable);
        Drawable getDrawable() const;

        void setVelocity(int velocity);
        int getVelocity(void) const;

        void setShootDmg(int shootDmg);
        int getShootDmg(void) const;

        void setShootVelocity(int shootVelocity);
        int getShootVelocity(void) const;

        void setShootGravity(int shootGravity);
        int getShootGravity(void) const;

        const unsigned char returnType(void);
    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        int _velocity;
        // Hitbox _hitbox;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
        // const unsigned char _type = TYPE_PLAYER;
};
