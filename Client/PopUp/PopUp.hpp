/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PopUp
*/

#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <chrono>
#include <memory>

#define POPUP_LAST_TIME 4000

namespace RType {
    class PopUp {
        public:
            PopUp(const std::string &text, const std::string &font);
            ~PopUp() {};
            void display(std::unique_ptr<sf::RenderWindow> &window);
            void setText(const std::string &text);
        private:
            sf::Font _font;
            std::chrono::steady_clock::time_point _timeout;
            sf::Text _text;
            sf::RectangleShape _rect;
    };
}
