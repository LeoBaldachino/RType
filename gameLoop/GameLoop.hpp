/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GameLoop
*/

#pragma once
#include "IGameLoop.hpp"
#include "../server/includes/ComCodes.hpp"

namespace RType {
    class GameLoop : public IGameLoop {
        public:
            GameLoop(Core &setCore);
            ~GameLoop();
            std::queue<Utils::MessageParsed_s> updateGameLoop(std::queue<Utils::MessageParsed_s> newMessages);
        protected:
            void setPositionEntityFromMsg(const Utils::MessageParsed_s &msg);
            void spawnEntityFromMsg(const Utils::MessageParsed_s &msg);
            Core &_core;
        private : 
            std::unordered_map<int, void (RType::GameLoop::*)(const Utils::MessageParsed_s &)> _commands;
    };
}
