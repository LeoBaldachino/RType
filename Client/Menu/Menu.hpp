/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Menu
*/

#pragma once
#include "../../Sockets/includes/SocketHandler.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../server/includes/ComCodes.hpp"
#include <SFML/Audio.hpp>
#include "../Prediction/Prediction.hpp"
#include <SFML/Graphics.hpp>
#include "BaseMenu.hpp"
#include "RoomSelector.hpp"
#include "../PopUp/PopUp.hpp"

namespace RType {
    enum Panel {
        loadingScreen,
        baseMenu,
        roomSelector
    };
    class Menu {
        public:
            Menu(PopUp &popUp);
            ~Menu();
            void displayMenu(std::unique_ptr<sf::RenderWindow> &window, bool mouseClicked);
            void addMessage(const Utils::MessageParsed_s &msg);
            inline bool closeMenu() const {return this->_closeMenu;};
            inline bool needToSendMessage() const {return !this->_toSend.empty();};
            inline Utils::MessageParsed_s sendMsg() {auto msg = this->_toSend.front();this->_toSend.pop(); return msg;};
            inline int getRoomId() const {return this->_roomSelector.getRoom();};
        private:
            std::mutex _mutex;
            std::queue<Utils::MessageParsed_s> _messagesQueue;
            std::queue<Utils::MessageParsed_s> _toSend;
            sf::Sprite _sprite;
            sf::Texture _text;
            Core _core;
            Panel _panel;
            BaseMenu _baseMenu;
            RoomSelector _roomSelector;
            bool _closeMenu;
            PopUp &_popUp;
    };
}
