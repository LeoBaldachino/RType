/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** LifeBar
*/

#pragma once

#include "../../Entity/Player.hpp"
#include "../../Core/Core.hpp"
#include "../../EntityTypes/EntityTypes.hpp"
#include "../../Visitor/SystemVisitor.hpp"
#include <array>
#include <chrono>
#define SCREEN_X 1920
#define SCREEN_Y 1080
#define UPDATE_PIXEL_TIME 10

namespace RType {
        class LifeBar {
            public:
                LifeBar();
                ~LifeBar();
                void setLifeBarToPlayer(const std::shared_ptr<Player> &player);
                void setLifeBarToBydos(const std::shared_ptr<Bydos> &by);
                void display(std::unique_ptr<sf::RenderWindow> &window);
            private:
                void clearFrameBuffer();
                sf::Texture _texture;
                sf::Sprite _sprite;
                sf::Uint8 *arr;
                std::mutex _mutex;
                std::chrono::steady_clock::time_point _updatePixels;
                std::queue<std::pair<unsigned int, unsigned int>> _toErase;
        };
}
