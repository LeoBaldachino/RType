/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bydos.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
// #include "../Components/Hitbox.hpp"
#include "../Components/Drawable.hpp"
#include "../Entity/Player.hpp"

class Bydos : public IEntity {
    public:
        Bydos() {};
        Bydos(Position position, int velocity, Vector2d moveDirection);
        ~Bydos() {};
        void accept(IVisitor &v, Player &p, std::unique_ptr<sf::RenderWindow> &window);

        Shoot shoot(const Position &playerPos) const;

        void setPosition(Position position);
        Position getPosition() const;

        void setState(State state);
        State getState() const;

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

    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        int _velocity;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
};
