/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomSelector
*/

#pragma once

#include "../Button/ButtonList.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../server/includes/ComCodes.hpp"

namespace RType {
    class RoomSelector {
        public:
            RoomSelector();
            ~RoomSelector();
            void display(std::unique_ptr<sf::RenderWindow> &toDraw);
            void hoverButtons(const sf::Vector2i &mousePos);
            void clickedButtons(const sf::Vector2i &mousePos);
            inline int getRoom() const {return this->_actualRoom;};
            void handleMessage(const Utils::MessageParsed_s &msg);
            Utils::MessageParsed_s sendMessage();
            bool needToSendMessage();
        private:
            ButtonList _list;
            int _actualRoom;
            bool _sendedMessage;
            Utils::MessageParsed_s _messageToSend;
            std::vector<unsigned char> _currentRoomList;
    };
}
