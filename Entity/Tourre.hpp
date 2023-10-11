/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Tourre.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Components/Drawable.hpp"
#include "../Entity/Player.hpp"

class Tourre : public IEntity {
    public:
        Tourre() {};
        Tourre(Position position, int velocity, Vector2d moveDirection);
        ~Tourre(){};

        void accept(IVisitor &v, Core &core);

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

        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);
        
        Vector2d getSize(void) { return (Vector2d(0, 0)); };

        bool getHasMoved(void);
        void setHasMoved(bool state);

    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        int _velocity;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
        bool _hasMoved = false;
};