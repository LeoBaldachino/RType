/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Dragon.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Entity/Player.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"
#include "../Components/Health.hpp"

#define DRAGONSHOOT_SPEED 3000
#define JUMP_SPEED 3000
#define MOVE_SPEED 3
#define DRAGON_X 667
#define DRAGON_Y 836
#define DRAGON_HEALTH 100

/**
 * @brief Class representing Dragon in the game
 */
class Dragon : public IEntity, public Health {
    public:
        /**
         * @brief Construct a new Dragon object
         */
        Dragon();
        /**
         * @brief Construct a new Dragon object
         * 
         * @param position Position of the Dragon
         */
        Dragon(Position position);
        ~Dragon(){};
        /**
         * @brief Accept method for visitor
         * 
         * @param v Visitor
         * @param core Core of the game
         */
        void accept(IVisitor &v, Core &core);
        /**
         * @brief Set the Position of the Dragon
         * 
         * @param position New position
         */
        void setPosition(const Position &position);
        /**
         * @brief Get the Position of the Dragon
         * 
         * @return Position object
         */
        Position getPosition() const;
        /**
         * @brief Set the State of the Dragon
         * 
         * @param state New state
         */
        /**
         * @brief Checks if the entity is ready to shoot
         * @return bool
         */
        inline bool readyToShoot() {return this->_readyShoot.clockOk();};

        void setState(State state);
        /**
         * @brief Get the State of the Dragon
         * 
         * @return State object
         */
        State getState() const;
        /**
         * @brief Set the Velocity of the Dragon
         * 
         * @param velocity New velocity
         */
        void setVelocity(int velocity);
        /**
         * @brief Get the Velocity of the Dragon
         * 
         * @return Velocity value
         */
        int getVelocity(void) const;
        /**
         * @brief Set the Moveable of the Dragon
         * 
         * @param moveable New moveable
         */
        void setMoveable(const Moveable &moveable);
        /**
         * @brief Get the Moveable of the Dragon
         * 
         * @return Moveable object
         */
        Moveable getMoveable(void) const;
        /**
         * @brief Check if the Dragon is colliding with another entity
         * @param entity Entity to check collision with
         * @return True if colliding, False otherwise
         */
        bool isColidingWith(IEntity &entity);
        /**
         * @brief Get the Size of the Dragon
         * 
         * @return Vector2d object
         */
        Vector2d getSize(void);
        /**
         * @brief Get the Type of the entity
         * 
         * @return Type of the entity
         */
        inline unsigned char getEntityType() {return RType::dragon;}
        /**
         * @brief Check if the Dragon is ready to move
         * 
         * @return True if ready, False otherwise
         */
        inline bool readyToMove() {return this->_readyMove.clockOk();};
        /**
         * @brief Check if the Dragon has moved
         * 
         * @return True if moved, False otherwise
         */
        bool getHasMoved(void);
        /**
         * @brief Set the Has Moved status of the Dragon
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

        bool getGoingUp(void) const;
        void setGoingUp(bool state);

    private:
        State _state;
        Position _position;
        Moveable _movement;
        int _velocity;
        Vector2d _size;
        bool _hasMoved = false;
        ClockTimer _readyShoot;
        ClockTimer _readyMove;
        unsigned int _spriteFrame = 0;
        ClockTimer _frameClock;
        ClockTimer _currentTempoState;
        bool _goingUp = true;
};