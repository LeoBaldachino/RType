/**
 * @file Player.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Player class definition
 */

#pragma once
#include "IEntity.hpp"
#include "../Components/Shoot.hpp"
#include "../Components/State.hpp"
#include "../Components/Drawable.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/Inputs.hpp"
#include "../Components/Health.hpp"
#include "../Components/ClockTimer.hpp"

#define PLAYER_X 32 * SIZE_SCALE
#define PLAYER_Y 14 * SIZE_SCALE
#define BASE_HEALTH 3
#define READY_MOVE 3

/**
 * @class Player
 * @brief Class representing a player in the game
 */
class Player : public IEntity, public Health {
    public:
        /**
         * @brief Construct a new Player object
         * @param position Position of the player
         */
        Player(Position position);
        Player();
        ~Player() {};

        /**
         * @brief Accept method for visitor pattern
         * @param v Visitor
         * @param core Core of the game
         */
        void accept(IVisitor &v, Core &core);

        /**
         * @brief Shoot method for the player
         * @return Shoot object
         */
        Shoot shoot() const;

        /**
         * @brief Move the player
         * @param direction Direction of the movement
         */
        void move(Vector2d direction);

        /**
         * @brief Set the Position of the player
         * @param position New position
         */
        void setPosition(const Position &position);

        /**
         * @brief Get the Position of the player
         * @return Position object
         */
        Position getPosition(void) const;

        /**
         * @brief Set the State of the player
         * @param state New state
         */
        void setState(State state);

        /**
         * @brief Get the State of the player
         * @return State object
         */
        State getState() const;

        /**
         * @brief Set the Moveable of the player
         * @param moveable New moveable
         */
        void setMoveable(const Moveable &moveable);

        /**
         * @brief Get the Moveable of the player
         * @return Moveable object
         */
        Moveable getMoveable() const;

        /**
         * @brief Set the Drawable of the player
         * @param drawable New drawable
         */
        void setDrawable(Drawable drawable);

        /**
         * @brief Get the Drawable of the player
         * @return Drawable object
         */
        Drawable getDrawable() const;

        /**
         * @brief Set the Velocity of the player
         * @param velocity New velocity
         */
        void setVelocity(int velocity);

        /**
         * @brief Get the Velocity of the player
         * @return Velocity value
         */
        int getVelocity(void) const;

        /**
         * @brief Set the Shoot Damage of the player
         * @param shootDmg New shoot damage
         */
        void setShootDmg(int shootDmg);

        /**
         * @brief Get the Shoot Damage of the player
         * @return Shoot damage value
         */
        int getShootDmg(void) const;

        /**
         * @brief Set the Shoot Velocity of the player
         * @param shootVelocity New shoot velocity
         */
        void setShootVelocity(int shootVelocity);

        /**
         * @brief Get the Shoot Velocity of the player
         * @return Shoot velocity value
         */
        int getShootVelocity(void) const;

        /**
         * @brief Set the Shoot Gravity of the player
         * @param shootGravity New shoot gravity
         */
        void setShootGravity(int shootGravity);

        /**
         * @brief Get the Shoot Gravity of the player
         * @return Shoot gravity value
         */
        int getShootGravity(void) const;

        /**
         * @brief Draw the player entity
         * @param window Window to draw on
         */
        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);

        /**
         * @brief Get the type of the entity
         * @return Type of the entity
         */
        const unsigned char returnType(void);

        /**
         * @brief Check if the player is colliding with another entity
         * @param entity Entity to check collision with
         * @return True if colliding, False otherwise
         */
        bool isColidingWith(IEntity &entity);

        /**
         * @brief Get the Has Moved status of the player
         * @return True if has moved, False otherwise
         */
        bool getHasMoved(void);

        /**
         * @brief Set the Has Moved status of the player
         * @param state New has moved status
         */
        void setHasMoved(bool state);

        /**
         * @brief Get the Size of the player
         * @return Vector2d object representing the size
         */
        Vector2d getSize(void);

        /**
         * @brief Get the Entity Type of the player
         * @return Entity type
         */
        inline unsigned char getEntityType() {return RType::player;};

        /**
         * @brief Check if the player is ready
         * @return True if ready, False otherwise
         */
        inline bool isReady() {return this->_timer.clockOk();};

        std::unique_ptr<Inputs> _inputs;
    private:
        State _state;
        Position _position;
        Moveable _movement;
        Drawable _drawable;
        ClockTimer _timer;
        int _velocity;
        int _shootDmg = 10;
        int _shootVelocity = 5;
        int _shootGravity = 0;
        Vector2d _size;
        bool _hasMoved = false;
};
