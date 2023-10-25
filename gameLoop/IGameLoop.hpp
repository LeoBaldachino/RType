/**
 * @file IGameLoop.hpp
 * @author EPITECH PROJECT, 2023
 * @brief IGameLoop class definition
 */

#pragma once
#include "../server/includes/Parser.hpp"
#include "../Core/Core.hpp"
#include "../Sockets/includes/MessageParsed.hpp"
#include "../EntityTypes/EntityTypes.hpp"

namespace RType {
    /**
     * @class IGameLoop
     * @brief IGameLoop class interface
     */
    class IGameLoop {
        public:
            /**
             * @brief Update game loop
             * @param newMessages New messages to process
             * @return std::queue<Utils::MessageParsed_s> Queue of parsed messages
             */
            virtual std::queue<Utils::MessageParsed_s> updateGameLoop(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages) = 0;
            
            /**
             * @brief Get entity type
             * @param id Entity ID
             * @return EntityTypes Entity type
             */
            virtual EntityTypes getEntityType(unsigned short id) = 0;

            /**
             * @brief Set the Enemies Waves
             * 
             * @param waves 
             */
            virtual void setEnemiesWaves(std::vector<std::map<Parser::Enemies, int>> waves) = 0;
        protected :
            /**
             * @brief Run after update
             * @param newMessages New messages to process
             * @return std::queue<Utils::MessageParsed_s> Queue of parsed messages
             */
            virtual std::queue<Utils::MessageParsed_s> runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages) = 0;
    };
}
