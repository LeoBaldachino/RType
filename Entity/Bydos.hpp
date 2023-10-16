/**
 * @file Bydos.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Bydos class definition
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

#define SHOOT_SPEED 600
#define MOVE_SPEED 3
#define BYDOS_X 21 * SIZE_SCALE
#define BYDOS_Y 24 * SIZE_SCALE
#define BYDOS_HEALTH 2

/**
 * @class Bydos
 * @brief Class representing a Bydos entity
 */
class Bydos : public IEntity, public Health {
    public:
        Bydos();
        Bydos(Position position, int velocity, Vector2d moveDirection);
        ~Bydos() {};

        /**
         * @brief Accepts a visitor and a core
         * @param v Visitor
         * @param core Core
         */
        void accept(IVisitor &v, Core &core);

        /**
         * @brief Shoots at a player's position
         * @param playerPos Player's position
         * @return Shoot
         */
        Shoot shoot(const Position &playerPos) const;

        /**
         * @brief Sets the position
         * @param position Position
         */
        void setPosition(const Position &position);

        /**
         * @brief Gets the position
         * @return Position
         */
        Position getPosition() const;

        /**
         * @brief Sets the state
         * @param state State
         */
        void setState(State state);

        /**
         * @brief Gets the state
         * @return State
         */
        State getState() const;

        /**
         * @brief Sets the drawable
         * @param drawable Drawable
         */
        void setDrawable(Drawable drawable);

        /**
         * @brief Gets the drawable
         * @return Drawable
         */
        Drawable getDrawable() const;

        /**
         * @brief Sets the velocity
         * @param velocity Velocity
         */
        void setVelocity(int velocity);

        /**
         * @brief Gets the velocity
         * @return int
         */
        int getVelocity(void) const;

        /**
         * @brief Sets the shoot damage
         * @param shootDmg Shoot damage
         */
        void setShootDmg(int shootDmg);

        /**
         * @brief Gets the shoot damage
         * @return int
         */
        int getShootDmg(void) const;

        /**
         * @brief Sets the shoot velocity
         * @param shootVelocity Shoot velocity
         */
        void setShootVelocity(int shootVelocity);

        /**
         * @brief Gets the shoot velocity
         * @return int
         */
        int getShootVelocity(void) const;

        /**
         * @brief Sets the shoot gravity
         * @param shootGravity Shoot gravity
         */
        void setShootGravity(int shootGravity);

        /**
         * @brief Gets the shoot gravity
         * @return int
         */
        int getShootGravity(void) const;

        /**
         * @brief Sets the moveable
         * @param moveable Moveable
         */
        void setMoveable(const Moveable &moveable);

        /**
         * @brief Gets the moveable
         * @return Moveable
         */
        Moveable getMoveable(void) const;

        /**
         * @brief Checks if the entity is colliding with another entity
         * @param entity Entity
         * @return bool
         */
        bool isColidingWith(IEntity &entity);

        /**
         * @brief Gets the size
         * @return Vector2d
         */
        Vector2d getSize(void);

        /**
         * @brief Draws the entity
         * @param window Window
         */
        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);

        /**
         * @brief Gets the entity type
         * @return unsigned char
         */
        inline unsigned char getEntityType() {return RType::bydos;}

        /**
         * @brief Checks if the entity is ready to shoot
         * @return bool
         */
        inline bool readyToShoot() {return this->_readyShoot.clockOk();};

        /**
         * @brief Checks if the entity is ready to move
         * @return bool
         */
        inline bool readyToMove() {return this->_readyMove.clockOk();};

        /**
         * @brief Gets the hasMoved state
         * @return bool
         */
        bool getHasMoved(void);

        /**
         * @brief Sets the hasMoved state
         * @param state State
         */
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
        Vector2d _size;
        bool _hasMoved = false;
        ClockTimer _readyShoot;
        ClockTimer _readyMove;
};
