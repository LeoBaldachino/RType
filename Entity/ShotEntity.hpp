/**
 * @file ShotEntity.hpp
 * @author EPITECH PROJECT, 2023
 * @brief ShotEntity class definition
 */

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "../Components/Drawable.hpp"
#include "IEntity.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Components/ClockTimer.hpp"

#define SHOT_X 32
#define SHOT_Y 12
#define MOVE_SHOT 1

/**
 * @class ShotEntity
 * @brief Class representing a shot entity in the game
 */
class ShotEntity : public IEntity {
    public:
        /**
         * @brief Construct a new ShotEntity object
         * @param shoot Shoot component of the entity
         * @param spriteFile Path to the sprite file
         * @param playerShoot Boolean indicating if the shot is from the player
         */
        ShotEntity(Shoot &shoot, std::string spriteFile, bool playerShoot);
        ~ShotEntity() {};

        /**
         * @brief Accept method for visitor pattern
         * @param v Visitor object
         * @param core Core object
         */
        void accept(IVisitor &v, Core &core);

        /**
         * @brief Draw the entity on the window
         * @param window Window to draw the entity on
         */
        void drawEntity(std::unique_ptr<sf::RenderWindow> &window);

        /**
         * @brief Get the Shoot object
         * @return Shoot object
         */
        Shoot getShoot(void) const;

        /**
         * @brief Set the Shoot object
         * @param shoot Shoot object to set
         */
        void setShoot(const Shoot &shoot);

        /**
         * @brief Get the Drawable object
         * @return Drawable object
         */
        Drawable getDrawable(void) const;

        /**
         * @brief Set the Drawable object
         * @param drawable Drawable object to set
         */
        void setDrawable(const Drawable &drawable);

        /**
         * @brief Get the Size of the entity
         * @return Vector2d size of the entity
         */
        Vector2d getSize(void);

        /**
         * @brief Check if the entity is colliding with another entity
         * @param entity Entity to check collision with
         * @return true if the entities are colliding, false otherwise
         */
        bool isColidingWith(IEntity &entity);

        /**
         * @brief Get the Moveable object
         * @return Moveable object
         */
        Moveable getMoveable(void) const;

        /**
         * @brief Set the Moveable object
         * @param moveable Moveable object to set
         */
        void setMoveable(const Moveable &moveable);

        /**
         * @brief Get the Position of the entity
         * @return Position of the entity
         */
        Position getPosition(void) const;

        /**
         * @brief Set the Position of the entity
         * @param position Position to set
         */
        void setPosition(const Position &position);

        /**
         * @brief Get the HasMoved state of the entity
         * @return true if the entity has moved, false otherwise
         */
        bool getHasMoved(void);

        /**
         * @brief Set the HasMoved state of the entity
         * @param state State to set
         */
        void setHasMoved(bool state);

        /**
         * @brief Get the EntityType of the entity
         * @return unsigned char representing the entity type
         */
        inline unsigned char getEntityType() {return _playerShoot ? RType::playerShoot : RType::bydosShoot;}

        /**
         * @brief Check if the entity is ready to move
         * @return true if the entity is ready to move, false otherwise
         */
        inline bool readyToMove() {return this->_clockMove.clockOk();};

    private:
        Shoot _shoot;
        Drawable _drawable;
        Vector2d _size;
        bool _hasMoved = false;
        bool _playerShoot;
        ClockTimer _clockMove;
};
