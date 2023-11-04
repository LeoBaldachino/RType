/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "../Components/ClockTimer.hpp"
#include "IEntity.hpp"
#include "../EntityTypes/EntityTypes.hpp"

#define PIERCING_SHOT_X 55
#define PIERCING_SHOT_Y 50
#define MOVE_PIERCING_SHOT 2
/**
 * @class PiercingShotEntity
 * @brief Class representing a piercing shot entity
 */
class PiercingShotEntity : public IEntity {
    public:
        /**
         * @brief Constructor
         * @param shoot Shoot component
         */
        PiercingShotEntity(Shoot &shoot, unsigned short sender);

        /**
         * @brief Destructor
         */
        ~PiercingShotEntity() {};

        /**
         * @brief Accept method for visitor pattern
         * @param v Visitor
         * @param core Core reference
         */
        void accept(IVisitor &v, Core &core);

        /**
         * @brief Get shoot component
         * @return Shoot component
         */
        Shoot getShoot(void) const;

        /**
         * @brief Set shoot component
         * @param shoot New shoot component
         */
        void setShoot(const Shoot &shoot);

        /**
         * @brief Get size of entity
         * @return Size of entity
         */
        Vector2d getSize(void);

        /**
         * @brief Check if entity is colliding with another
         * @param entity Entity to check collision with
         * @return True if colliding, false otherwise
         */
        bool isColidingWith(IEntity &entity);

        /**
         * @brief Get moveable component
         * @return Moveable component
         */
        Moveable getMoveable(void) const;

        /**
         * @brief Set moveable component
         * @param moveable New moveable component
         */
        void setMoveable(const Moveable &moveable);

        /**
         * @brief Get position of entity
         * @return Position of entity
         */
        Position getPosition(void) const;

        /**
         * @brief Set position of entity
         * @param position New position
         */
        void setPosition(const Position &position);

        /**
         * @brief Get entity type
         * @return Entity type
         */
        inline unsigned char getEntityType() {return RType::percingShoot;}

        /**
         * @brief Get has moved state
         * @return Has moved state
         */
        bool getHasMoved(void);

        /**
         * @brief Set has moved state
         * @param state New state
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
        std::vector<float> getEntityPositionRange() {return std::vector<float>{0, 0, 0, 0, 0, 0};};

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

        /**
         * @brief Check if the entity is ready to move
         * @return true if the entity is ready to move, false otherwise
         */
        inline bool readyToMove() {return this->_clockMove.clockOk();};

        inline unsigned short getSender() {return this->_sender;};
    private:
        Shoot _shoot;
        Vector2d _size;
        bool _hasMoved = false;
        unsigned int _spriteFrame = 0;
        ClockTimer _frameClock;
        ClockTimer _clockMove;
        ClockTimer _currentTempoState;
        unsigned short _sender;
};
