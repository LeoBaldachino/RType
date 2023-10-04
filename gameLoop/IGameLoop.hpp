/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IGameLoop
*/

#pragma once
#include "../Core/Core.hpp"
#include "../Sockets/includes/MessageParsed.hpp"
#include "../server/includes/EntityTypes.hpp"

namespace RType {
    class IGameLoop {
        public:
            virtual std::queue<Utils::MessageParsed_s> updateGameLoop(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages) = 0;
            virtual EntityTypes getEntityType(unsigned short id) = 0;
        protected :
            virtual std::queue<Utils::MessageParsed_s> runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages) = 0;
    };
}
