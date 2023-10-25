/**
 * @file LifeBar.hpp
 * @author EPITECH PROJECT, 2023
 * @brief LifeBar class definition
 */

#pragma once

#include "../../Entity/Player.hpp"
#include <SFML/Graphics.hpp>
#include "../../Core/Core.hpp"
#include "../../EntityTypes/EntityTypes.hpp"
#include "../../Visitor/SystemVisitor.hpp"
#include <array>
#include <chrono>

#define SCREEN_X 1920
#define SCREEN_Y 1080
#define UPDATE_PIXEL_TIME 10

namespace RType {
    /**
     * @class LifeBar
     * @brief Class representing a life bar in the RType game
     */
    class LifeBar {
        public:
            /**
             * @brief Constructor for LifeBar
             */
            LifeBar();

            /**
             * @brief Destructor for LifeBar
             */
            ~LifeBar();

            /**
             * @brief Set the LifeBar to a Player
             * @param player Shared pointer to a Player
             */
            void setLifeBarToPlayer(const std::shared_ptr<Player> &player);

            /**
             * @brief Set the LifeBar to a Bydos
             * @param by Shared pointer to a Bydos
             */
            void setLifeBarToBydos(const std::shared_ptr<Bydos> &by);
            /**
             * @brief Set the Life Bar to a Tourre
             * 
             * @param by Shared pointer to a Tourre
             */
            void setLifeBarToTourre(const std::shared_ptr<Tourre> &by);

            /**
             * @brief Display the LifeBar
             * @param window Unique pointer to a RenderWindow
             */
            void display(std::unique_ptr<sf::RenderWindow> &window);

        private:
            /**
             * @brief Clear the frame buffer
             */
            void clearFrameBuffer();

            sf::Texture _texture; ///< Texture of the LifeBar
            sf::Sprite _sprite; ///< Sprite of the LifeBar
            std::unique_ptr<sf::Uint8 []> _pixels; ///< Pixels of the LifeBar
            std::mutex _mutex; ///< Mutex for thread safety
            std::chrono::steady_clock::time_point _updatePixels; ///< Time point for updating pixels
            std::queue<std::pair<unsigned int, unsigned int>> _toErase; ///< Queue of pairs to erase
    };
}
