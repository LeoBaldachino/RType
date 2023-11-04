/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** BaseMenu
*/

#pragma once
#include "../Button/ButtonList.hpp"

namespace RType {
    class BaseMenu {
        public:
            BaseMenu();
            ~BaseMenu();
            void display(std::unique_ptr<sf::RenderWindow> &toDraw);
            void hoverButtons(const sf::Vector2i &mousePos);
            void clickedButtons(const sf::Vector2i &mousePos);
            inline bool exited() const {return this->_exited;};
        private:
            ButtonList _list;
            bool _exited;
    };
}
