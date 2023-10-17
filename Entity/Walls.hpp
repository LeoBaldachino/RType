/**
 * @file Walls.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Walls class definition
 */

#pragma once

#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Components/Hitbox.hpp"

/**
 * @class Walls
 * @brief Class representing Walls in the game
 */
class Walls {
    public:
        /**
         * @brief Construct a new Walls object
         * 
         * @param position Position of the Walls
         * @param velocity Velocity of the Walls
         * @param moveDirection Direction of the Walls movement
         */
        Walls(Position position, int velocity, Vector2d moveDirection);

        /**
         * @brief Destroy the Walls object
         */
        ~Walls(){};
        
        /**
         * @brief Return if the position range of the entity and the temporisation, returns four 0 if no range
         * 
         * @param frame 
         */
        std::vector<int> getEntityPositionRange() {return std::vector<int>(4, 0);};

    private:
        Position _position; ///< Position of the Walls
        Moveable _movement; ///< Movement of the Walls
        // Hitbox _hitbox; ///< Hitbox of the Walls
};
