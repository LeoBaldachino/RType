/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RTypeGameLoop
*/

#pragma once
#include "../GameLoop.hpp"
#include "../../Visitor/SystemVisitor.hpp"
namespace RType {
    class RTypeGameLoop : public GameLoop {
        public:
            RTypeGameLoop(Core &core);
            ~RTypeGameLoop();
            EntityTypes getEntityType(unsigned short id);
        protected :
            std::queue<Utils::MessageParsed_s> runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages);
        private :
            void updatePlayerPos(std::pair<unsigned short, Utils::MessageParsed_s> msg);
            void handleBydos(std::queue<Utils::MessageParsed_s> &toReturn);
            void addRemoveEntity(std::queue<Utils::MessageParsed_s> &toReturn, unsigned short id);
            void checkPlayerStatus(std::queue<Utils::MessageParsed_s> &toReturn);
            SystemVisitor v;
            std::vector<unsigned short> _bydos;
    };
}
