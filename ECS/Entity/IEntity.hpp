/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Visitor/IVisitor.hpp"
#include "../Components/ClockTimer.hpp"

#define SIZE_SCALE 2

/**
 * @class IEntity
 * @brief Class representing an entity
 */
class IEntity {
    public:
        /**
         * @brief Accept a visitor and a core
         * @param v Visitor
         * @param core Core
         */
        virtual void accept(IVisitor &v, Core &core) = 0;

        /**
         * @brief Set the Moveable of the entity
         * @param moveable New moveable
         */
        virtual void setMoveable(const Moveable &moveable) = 0;

        /**
         * @brief Get the Moveable of the entity
         * @return Moveable object
         */
        virtual Moveable getMoveable(void) const = 0;

        /**
         * @brief Set the Position of the entity
         * @param position New position
         */
        virtual void setPosition(const Position &position) = 0;

        /**
         * @brief Get the Position of the entity
         * @return Position object
         */
        virtual Position getPosition(void) const = 0;

        /**
         * @brief Get the size of the entity
         * @return Vector2d object
         */
        virtual Vector2d getSize(void) = 0;

        /**
         * @brief Get the move state of the entity
         * @return bool
         */
        virtual bool getHasMoved(void) = 0;

        /**
         * @brief Set the move state of the entity
         * @param state New state
         */
        virtual void setHasMoved(bool state) = 0;

        /**
         * @brief Get the type of the entity
         * @return unsigned char
         */
        virtual unsigned char getEntityType() = 0;

        /**
         * @brief Get the Entity Sprite Frame count
         * 
         * @return unsigned int 
         */
        virtual unsigned int getEntitySpriteFrame() = 0;

        /**
         * @brief Return if the position range of the entity and the temporisation, returns four 0 if no range
         * 
         * @param frame 
         */
        virtual std::vector<float> getEntityPositionRange() = 0;

        /**
         * @brief Set the Tempo State of the entity
         * 
         * @param state New tempo state
         */
        virtual void setTempoState(ClockTimer state) = 0;

        /**
         * @brief Get the Tempo State
         * 
         * @return ClockTimer 
         */
        virtual ClockTimer getTempoState() = 0;
};
