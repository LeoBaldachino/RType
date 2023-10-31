/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DragonShot.hpp
*/

#pragma once
#include "IEntity.hpp"
#include "../Components/State.hpp"
#include "../Systems/Subsystems/AIShoot.hpp"
#include "../Entity/Player.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"
#include "../Components/Health.hpp"

#define MOVE_SPEED 3
#define DRAGONSHOT_X 130
#define DRAGONSHOT_Y 130
#define DRAGONSHOT_HEALTH 1

/**
 * @brief Class representing DragonShot in the game
 */
class DragonShot : public IEntity, public Health {
    public:
        /**
         * @brief Construct a new DragonShot object
         */
        DragonShot();
        /**
         * @brief Construct a new DragonShot object
         * 
         * @param position Position of the DragonShot
         */
        DragonShot(Position position);
        ~DragonShot(){};
        /**
         * @brief Accept method for visitor
         * 
         * @param v Visitor
         * @param core Core of the game
         */
        void accept(IVisitor &v, Core &core);
        /**
         * @brief Set the Position of the DragonShot
         * 
         * @param position New position
         */
        void setPosition(const Position &position);
        /**
         * @brief Get the Position of the DragonShot
         * 
         * @return Position object
         */
        Position getPosition() const;
        /**
         * @brief Set the State of the DragonShot
         * 
         * @param state New state
         */
        void setState(State state);
        /**
         * @brief Get the State of the DragonShot
         * 
         * @return State object
         */
        State getState() const;
        /**
         * @brief Set the Velocity of the DragonShot
         * 
         * @param velocity New velocity
         */
        void setVelocity(int velocity);
        /**
         * @brief Get the Velocity of the DragonShot
         * 
         * @return Velocity value
         */
        int getVelocity(void) const;
        /**
         * @brief Set the Moveable of the DragonShot
         * 
         * @param moveable New moveable
         */
        void setMoveable(const Moveable &moveable);
        /**
         * @brief Get the Moveable of the DragonShot
         * 
         * @return Moveable object
         */
        Moveable getMoveable(void) const;
        /**
         * @brief Check if the DragonShot is colliding with another entity
         * @param entity Entity to check collision with
         * @return True if colliding, False otherwise
         */
        bool isColidingWith(IEntity &entity);
        /**
         * @brief Get the Size of the DragonShot
         * 
         * @return Vector2d object
         */
        Vector2d getSize(void);
        /**
         * @brief Get the Type of the entity
         * 
         * @return Type of the entity
         */
        inline unsigned char getEntityType() {return RType::dragonShot;}
        /**
         * @brief Check if the DragonShot is ready to move
         * 
         * @return True if ready, False otherwise
         */
        inline bool readyToMove() {return this->_readyMove.clockOk();};
        /**
         * @brief Check if the DragonShot has moved
         * 
         * @return True if moved, False otherwise
         */
        bool getHasMoved(void);
        /**
         * @brief Set the Has Moved status of the DragonShot
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

        Position getOriginalPos(void) const;
        void setGoingUp(bool state);
        bool getGoingUp(void) const;

    private:
        State _state;
        Position _position;
        Moveable _movement;
        int _velocity;
        Vector2d _size;
        bool _hasMoved = false;
        ClockTimer _readyMove;
        unsigned int _spriteFrame = 0;
        ClockTimer _frameClock;
        ClockTimer _currentTempoState;
        Position _originalPos;
        bool _goingUp = true;
};
