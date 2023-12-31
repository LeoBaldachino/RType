/**
 * @file GameLoop.hpp
 * @author EPITECH PROJECT, 2023
 * @brief GameLoop class definition
 */

#pragma once
#include "IGameLoop.hpp"
#include "../server/includes/ComCodes.hpp"

#include <array>

namespace RType {
    /**
     * @class GameLoop
     * @brief GameLoop class inheriting from IGameLoop
     */
    class GameLoop : public IGameLoop {
        public:
            /**
             * @brief Construct a new Game Loop object
             * 
             * @param setCore reference to Core object
             */
            GameLoop(Core &setCore);

            /**
             * @brief Destroy the Game Loop object
             */
            ~GameLoop() {};

            /**
             * @brief Update game loop
             * 
             * @param newMessages queue of new messages
             * @return std::queue<Utils::MessageParsed_s> updated queue of messages
             */
            std::queue<Utils::MessageParsed_s> updateGameLoop(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages);
            /**
             * @brief Get the details of a player
             * 
             * @param playerId 
             * @return std::tuple<unsigned short, unsigned short, unsigned short, unsigned short> 
             */
            std::tuple<unsigned short, unsigned short, unsigned short, unsigned short> getPlayerDetails(unsigned char playerId);
        protected:
            /**
             * @brief Add Player object
             * 
             * @param msg message parsed
             * @param id id of the player
             */
            void addPlayer(const Utils::MessageParsed_s &msg, unsigned short id);

            /**
             * @brief Remove Player object
             * 
             * @param msg message parsed
             * @param id id of the player
             */
            void removePlayer(const Utils::MessageParsed_s &msg, unsigned short id);

            /**
             * @brief Core object
             */
            Core &_core;

            /**
             * @brief Array of player ids
             */
            std::vector<unsigned short> _playerArray;
            
            /**
             * @brief Set the Enemies Waves
             * 
             * @param waves 
             */
            void setEnemiesWaves(std::vector<std::map<Parser::Enemies, int>> waves) {};
        private : 
            /**
             * @brief Map of commands
             */
            std::unordered_map<int, void (RType::GameLoop::*)(const Utils::MessageParsed_s &msg, unsigned short)> _commands;
    };
}
