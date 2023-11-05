/**
 * @file RTypeGameLoop.hpp
 * @author EPITECH PROJECT, 2023
 * @brief RTypeGameLoop class definition
 */

#pragma once
#include "../GameLoop.hpp"
#include "../../Visitor/SystemVisitor.hpp"
#define TARGET_FPS 30
#define REFRESH_ALL_ENTITIES 1000 / 30
#define STATUS_ALL_ENTITES 1000 / 20
#define REFRESH_PLAYERS 1000

namespace RType {
    /**
     * @class RTypeGameLoop
     * @brief RTypeGameLoop class inheriting from GameLoop
     */
    class RTypeGameLoop : public GameLoop {
        public:
            /**
             * @brief Construct a new RTypeGameLoop object
             * 
             * @param core reference to Core object
             */
            RTypeGameLoop(Core &core);

            /**
             * @brief Destroy the RTypeGameLoop object
             */
            ~RTypeGameLoop() {};

            /**
             * @brief Get entity type
             * @param id Entity ID
             * @return EntityTypes The type of the entity
             */
            EntityTypes getEntityType(unsigned short id);
        protected :
            /**
             * @brief Run after update
             * @param newMessages New messages to process
             * @return std::queue<Utils::MessageParsed_s> Queue of parsed messages
             */
            std::queue<Utils::MessageParsed_s> runAfterUpdate(std::queue<std::pair<unsigned short, Utils::MessageParsed_s>> newMessages);
        private :
            /**
             * @brief Update player position
             * @param msg Message containing player position
             */
            void updatePlayerPos(std::pair<unsigned short, Utils::MessageParsed_s> msg);

            /**
             * @brief Handle Bydos
             * @param toReturn Queue of messages to return
             */
            void handleBydos(std::queue<Utils::MessageParsed_s> &toReturn);

            void handleTourre(std::queue<Utils::MessageParsed_s> &toReturn);

            void handleCoin(std::queue<Utils::MessageParsed_s> &toReturn);

            /**
             * @brief Add or remove entity
             * @param toReturn Queue of messages to return
             * @param id ID of the entity to add or remove
             */
            void addRemoveEntity(std::queue<Utils::MessageParsed_s> &toReturn, unsigned short id);

            /**
             * @brief Check player status
             * @param toReturn Queue of messages to return
             */
            void checkPlayerStatus(std::queue<Utils::MessageParsed_s> &toReturn);

            /**
             * @brief Check Bydos status
             * @param toReturn Queue of messages to return
             */
            void checkBydosStatus(std::queue<Utils::MessageParsed_s> &toReturn);

            void checkTourreStatus(std::queue<Utils::MessageParsed_s> &toReturn);

            /**
             * @brief Send refresh all entities
             * @param toReturn Queue of messages to return
             */
            void sendRefreshAllEntities(std::queue<Utils::MessageParsed_s> &toReturn);

            /**
             * @brief Send refresh players
             * @param toReturn Queue of messages to return
             */
            void sendRefreshPlayers(std::queue<Utils::MessageParsed_s> &toReturn);

            /**
             * @brief Handle enemies' waves
             * 
             * @param toReturn 
             */
            void handleWaves(std::queue<Utils::MessageParsed_s> &toReturn);

            /**
             * @brief Set the Enemies Waves
             * 
             * @param waves 
             */
            void setEnemiesWaves(std::vector<std::map<Parser::Enemies, int>> waves);
            void refreshStatus(std::queue<Utils::MessageParsed_s> &toReturn);
            void sendNbOfEntites(std::queue<Utils::MessageParsed_s> &toReturn);
            SystemVisitor v;
            std::vector<unsigned short> _bydos;
            std::vector<unsigned short> _tourre;
            std::vector<unsigned short> _coin;
            unsigned short _genie = -1;
            unsigned short _mermaid = -1;
            unsigned short _dragon = -1;
            std::chrono::steady_clock::time_point _refreshAllEntities;
            std::chrono::steady_clock::time_point _refreshPlayers;
            std::vector<std::map<Parser::Enemies, int>> _waves;
            std::chrono::steady_clock::time_point _refreshStatus;
    };
}
