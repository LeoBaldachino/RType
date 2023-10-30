/**
 * @file Genie.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Genie class definition
 */

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Entity/Player.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"
#include "../Components/Health.hpp"

#define SHOOT_SPEED 3000
#define JUMP_SPEED 3000
#define MOVE_SPEED 3
#define GENIE_X 247 * SIZE_SCALE
#define GENIE_Y 220 * SIZE_SCALE
#define GENIE_HEALTH 2

/**
 * @brief Class representing Genie in the game
 */
class Genie : public IEntity, public Health {
    public:
        /**
         * @brief Construct a new Genie object
         */
        Genie();
        /**
         * @brief Construct a new Genie object
         * 
         * @param position Position of the Genie
         * @param velocity Velocity of the Genie
         * @param moveDirection Direction of the Genie movement
         */
        Genie(Position position, int velocity, Vector2d moveDirection);
        ~Genie(){};
        /**
         * @brief Accept method for visitor
         * 
         * @param v Visitor
         * @param core Core of the game
         */
        void accept(IVisitor &v, Core &core);
        /**
         * @brief Set the Position of the Genie
         * 
         * @param position New position
         */
        void setPosition(const Position &position);
        /**
         * @brief Get the Position of the Genie
         * 
         * @return Position object
         */
        Position getPosition() const;
        /**
         * @brief Set the State of the Genie
         * 
         * @param state New state
         */
        void setState(State state);
        /**
         * @brief Get the State of the Genie
         * 
         * @return State object
         */
        State getState() const;
        /**
         * @brief Set the Velocity of the Genie
         * 
         * @param velocity New velocity
         */
        void setVelocity(int velocity);
        /**
         * @brief Get the Velocity of the Genie
         * 
         * @return Velocity value
         */
        int getVelocity(void) const;
        /**
         * @brief Set the Moveable of the Genie
         * 
         * @param moveable New moveable
         */
        void setMoveable(const Moveable &moveable);
        /**
         * @brief Get the Moveable of the Genie
         * 
         * @return Moveable object
         */
        Moveable getMoveable(void) const;
        /**
         * @brief Check if the Genie is colliding with another entity
         * @param entity Entity to check collision with
         * @return True if colliding, False otherwise
         */
        bool isColidingWith(IEntity &entity);
        /**
         * @brief Get the Size of the Genie
         * 
         * @return Vector2d object
         */
        Vector2d getSize(void);
        /**
         * @brief Get the Type of the entity
         * 
         * @return Type of the entity
         */
        inline unsigned char getEntityType() {return RType::genie;}
        /**
         * @brief Check if the Genie is ready to move
         * 
         * @return True if ready, False otherwise
         */
        inline bool readyToMove() {return this->_readyMove.clockOk();};
        /**
         * @brief Check if the Genie has moved
         * 
         * @return True if moved, False otherwise
         */
        bool getHasMoved(void);
        /**
         * @brief Set the Has Moved status of the Genie
         * 
         * @param state New has moved status
         */
        void setHasMoved(bool state);
        /**
         * @brief Get the Entity Sprite Frame count
         * 
         * @return unsigned int 
         */
        unsigned int getEntitySpriteFrame();

        /**
         * @brief Return if the position range of the entity and the temporisation, returns four 0 if no range
         * 
         * @param frame 
         */
        std::vector<float> getEntityPositionRange();

        /**
         * @brief Set the Tempo State
         * 
         * @param state New tempo state
         */
        void setTempoState(ClockTimer state);

        /**
         * @brief Get the Tempo State
         * 
         * @return ClockTimer 
         */
        ClockTimer getTempoState(void);

    private:
        State _state;
        Position _position;
        Moveable _movement;
        int _velocity;
        // int _shootDmg = 10;
        // int _shootVelocity = 5;
        // int _shootGravity = 0;
        Vector2d _size;
        bool _hasMoved = false;
        ClockTimer _readyShoot;
        ClockTimer _readyMove;
        unsigned int _spriteFrame = 0;
        ClockTimer _frameClock;
        ClockTimer _currentTempoState;
};