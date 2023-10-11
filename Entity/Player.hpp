/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Player.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/Shoot.hpp"
#include "../Components/State.hpp"
#include "../Components/Drawable.hpp"
#include "EntityType.hpp"
#include "../Components/Inputs.hpp"
#define PLAYER_X 32 * SIZE_SCALE
#define PLAYER_Y 14 * SIZE_SCALE

class Player : public IEntity {
    public:
        Player(Position position);
        Player() {};
        ~Player() {};
        void accept(IVisitor &v, Core &core);

        Shoot shoot() const;

        void move(Vector2d direction);

        void setPosition(const Position &position);
        Position getPosition(void) const;

        void setState(State state);
        State getState() const;

        void setMoveable(const Moveable &moveable);
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

        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);

        const unsigned char returnType(void);

        bool isColidingWith(IEntity &entity);

        bool getHasMoved(void);
        void setHasMoved(bool state);

        Vector2d getSize(void);
        inline unsigned char getEntityType() {return player;}
        Inputs _inputs;
    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        int _velocity;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
        // const unsigned char _type = TYPE_PLAYER;
        Vector2d _size;
        bool _hasMoved = false;
};
