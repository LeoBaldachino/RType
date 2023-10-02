/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Bydos.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Components/Drawable.hpp"
#include "../Entity/Player.hpp"
#include "../Components/Vector2d.hpp"

#define BYDOS_X 21 * SIZE_SCALE
#define BYDOS_Y 24 * SIZE_SCALE

class Bydos : public IEntity {
    public:
        Bydos() {};
        Bydos(Position position, int velocity, Vector2d moveDirection);
        ~Bydos() {};
        void accept(IVisitor &v, std::unique_ptr<sf::RenderWindow> &window);

        Shoot shoot(const Position &playerPos) const;

        void setPosition(const Position &position);
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

        void setMoveable(const Moveable &moveable);
        Moveable getMoveable(void) const;

        bool isColidingWith(IEntity &entity);
        Vector2d getSize(void);
    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        int _velocity;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
        Vector2d _size;
};
