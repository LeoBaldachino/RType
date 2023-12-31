/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ButtonList
*/

#pragma once
#include "Button.hpp"
#include <unordered_map>
#include <exception>

namespace RType {
    class ButtonList {
        public:
            ButtonList(const std::string &fontPath);
            ~ButtonList() {};
            void addButtons(const std::function<void()>& handler, const std::string &path, const std::string &text, const sf::Vector2f pos, const sf::IntRect rect, int decalHover, unsigned int id);
            void removeButton(unsigned int id);
            void displayButtons(std::unique_ptr<sf::RenderWindow> &window);
            void hoverButtons(const sf::Vector2i &mousePos);
            void clickButtons(const sf::Vector2i &mousePos);
            inline size_t getLength() const {return this->_buttons.size();};
            inline sf::Font getFont() const {return this->_buttonsFont;};
        private:
            std::unordered_map<unsigned int, std::unique_ptr<Button>> _buttons;
            sf::Font _buttonsFont;
    };
}
