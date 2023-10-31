/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomEditor
*/

#pragma once

#include "../Button/ButtonList.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../server/includes/ComCodes.hpp"
#include <thread>

namespace RType {
    class RoomEditor {
        public:
            RoomEditor(bool &sendMsg, Utils::MessageParsed_s &msg, int &sizeNb);
            ~RoomEditor();
            void display(std::unique_ptr<sf::RenderWindow> &toDraw);
            inline void hoverButtons(const sf::Vector2i &mousePos) {this->_list.hoverButtons(mousePos);};
            inline void clickedButtons(const sf::Vector2i &mousePos) {this->_list.clickButtons(mousePos);};
            inline unsigned char getNbOfPlayers() const {return this->_nbOfPlayers;};
            inline unsigned char getBaseLifePlayer() const {return this->_baseLifePlayer;};
        private:
            ButtonList _list;
            unsigned char _nbOfPlayers;
            unsigned char _baseLifePlayer;
            bool &_sendMsg;
            Utils::MessageParsed_s &_msg;
            sf::Text _text;
            sf::Font _font;
            sf::Vector2f _posLife;
            sf::Vector2f _posNbPlayer;
            int &_sizeNb;
    };
}
