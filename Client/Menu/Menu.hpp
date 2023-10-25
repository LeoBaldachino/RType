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

namespace RType {
    class Menu {
        public:
            Menu();
            ~Menu();
            void displayMenu(std::unique_ptr<sf::RenderWindow> &window);
            void addMessage(const Utils::MessageParsed_s &msg);
        private:
            std::mutex _mutex;
            std::queue<Utils::MessageParsed_s> _messagesQueue;
            Core _core;
    };
}
