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
#include "../Components/Controlable.hpp"
// #include "../Components/Hitbox.hpp"
#include "../Components/Moveable.hpp"

class Player : public IEntity {
    public:
        Player(Position position);
        ~Player() {};
        void accept(SystemVisitor &v);

        Shoot shoot() const;

        void handleInput(std::unique_ptr<sf::RenderWindow> &window);

        void move(Vector2d direction);

        void setPosition(Position position);
        Position getPosition() const;

        // void setHitbox(Hitbox hitbox);
        // Hitbox getHitbox() const;

        void setState(State state);
        State getState() const;

        void setMoveable(Moveable moveable);
        Moveable getMoveable() const;

    private:
        State _state;
        Position _position;
        Moveable _movement;
        Controlable _controlable;
        int _velocity;
        // Hitbox _hitbox;
        int _shootDmg = 10;
        int _shootVelocity = 10;
        int _shootGravity = 0;
};
