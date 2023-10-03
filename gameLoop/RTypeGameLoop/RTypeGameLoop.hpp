/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RTypeGameLoop
*/

#pragma once
#include "../GameLoop.hpp"

namespace RType {
    class RTypeGameLoop : public GameLoop {
        public:
            RTypeGameLoop(Core &core);
            ~RTypeGameLoop();
        protected :
            std::queue<Utils::MessageParsed_s> runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages);
        private :
        
    };
}
