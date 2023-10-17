/**
 * @file PiercingShotEntity.hpp
 * @author EPITECH PROJECT, 2023
 * @brief PiercingShotEntity class definition
 */

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "IEntity.hpp"
#include "../EntityTypes/EntityTypes.hpp"

#define PIERCING_SHOT_X 80
#define PIERCING_SHOT_Y 16

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
        PiercingShotEntity(Shoot &shoot);

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

    private:
        Shoot _shoot;
        Vector2d _size;
        bool _hasMoved = false;
};
