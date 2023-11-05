/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MessagePanel
*/

#pragma once

#include "../../Sockets/includes/SocketHandler.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../server/includes/ComCodes.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../PopUp/PopUp.hpp"
#include "../Button/ButtonList.hpp"


namespace RType {
    class MessagePanel {
        public :
            MessagePanel();
            ~MessagePanel() {};
            void display(std::unique_ptr<sf::RenderWindow> &window);
            inline bool needSendMessage()  {bool ret = this->_readyToSend; this->_readyToSend = false; return ret;};
            inline void openPanel() {this->_isOpen = true;};
            inline void closePanel() {this->_isOpen = false;};
            inline bool isOpen() const {return this->_isOpen;};
            Utils::MessageParsed_s sendMessage();
            void hoverButtons(const sf::Vector2i &mousePos);
            void clickButtons(const sf::Vector2i &mousePos);
            std::string decyptMessage(const Utils::MessageParsed_s &msg);
        private : 
            bool _readyToSend;
            bool _isOpen;
            std::vector<unsigned char> _message;
            std::vector<std::string> _messageText;
            ButtonList _list;
            std::array<std::string , 38> _alltexts;
            int _actText;
            sf::Text _globText;
            sf::Font _font;
    };
}
