/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Button
*/

#pragma once
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <chrono>

namespace RType {
    class Button {
        public:
            Button(const std::function<void()>& handler, const std::string &path, const std::string &text, const sf::Vector2f pos, const sf::IntRect rect, int decalHover);
            ~Button();
            void checkClicked(const sf::Vector2i &pos);
            void checkHover(const sf::Vector2i &pos);
            void display(std::unique_ptr<sf::RenderWindow> &window);
        private:
            const std::function<void()>& _handler;
            const std::string _path;
            const std::string _text;
            const sf::Vector2f _pos;
            sf::IntRect _rectCheck;
            sf::Rect<int> _rect;
            const int _decalHover;
            int _actPosHover;
            sf::Sprite _sprite;
            sf::Texture _texture;
            std::chrono::steady_clock::time_point _timeout;
    };
}
