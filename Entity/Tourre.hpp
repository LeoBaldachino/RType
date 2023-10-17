/**
 * @file Tourre.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Tourre class definition
 */

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Components/Drawable.hpp"
#include "../Entity/Player.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"
#include "../Components/Health.hpp"

#define SHOOT_SPEED 3000
#define JUMP_SPEED 3000
#define MOVE_SPEED 3
#define TOURRE_X 50 * SIZE_SCALE
#define TOURRE_Y 60 * SIZE_SCALE
#define TOURRE_HEALTH 2

/**
 * @brief Class representing Tourre in the game
 */
class Tourre : public IEntity, public Health {
    public:
        Tourre();
        Tourre(Position position, int velocity, Vector2d moveDirection);
        ~Tourre(){};

        void accept(IVisitor &v, Core &core);

        // Shoot shoot(const Position &playerPos) const;

        void setPosition(const Position &position);
        Position getPosition() const;

        void setState(State state);
        State getState() const;

        void setDrawable(Drawable drawable);
        Drawable getDrawable() const;

        void setVelocity(int velocity);
        int getVelocity(void) const;

        // void setShootDmg(int shootDmg);
        // int getShootDmg(void) const;

        // void setShootVelocity(int shootVelocity);
        // int getShootVelocity(void) const;

        // void setShootGravity(int shootGravity);
        // int getShootGravity(void) const;

        void setMoveable(const Moveable &moveable);
        Moveable getMoveable(void) const;

        bool isColidingWith(IEntity &entity);

        Vector2d getSize(void);

        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);
        
        inline unsigned char getEntityType() {return RType::tourre;}

        // inline bool readyToShoot() {return this->_readyShoot.clockOk();};

        inline bool readyToMove() {return this->_readyMove.clockOk();};

        bool getHasMoved(void);

        void setHasMoved(bool state);

    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        int _velocity;
        // int _shootDmg = 10;
        // int _shootVelocity = 5;
        // int _shootGravity = 0;
        Vector2d _size;
        bool _hasMoved = false;
        ClockTimer _readyShoot;
        ClockTimer _readyMove;
};