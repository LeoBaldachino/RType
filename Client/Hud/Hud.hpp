/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Hud
*/

#pragma once
#include "../Button/ButtonList.hpp"

namespace RType {
    class Hud {
        public:
            Hud(const sf::Vector2f &pos);
            ~Hud();
            void display(std::unique_ptr<sf::RenderWindow> &toDraw);
            inline void setScore(unsigned char score) {this->_score = score;};
        private:
            unsigned char _score;
            sf::Font _font;
            sf::Text _text;
            sf::Vector2f _pos;
    };
}
