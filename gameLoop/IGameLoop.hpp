/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IGameLoop
*/

#pragma once
#include "../Core/Core.hpp"
#include "../Sockets/includes/MessageParsed.hpp"

namespace RType {
    class IGameLoop {
        public:
            virtual std::queue<Utils::MessageParsed_s> updateGameLoop(std::queue<Utils::MessageParsed_s> newMessages) = 0;
        protected :
            virtual std::queue<Utils::MessageParsed_s> runAfterUpdate(std::queue<Utils::MessageParsed_s> newMessages) = 0;
    };
}
