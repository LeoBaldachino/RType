/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Room
*/

#pragma once
#include <iostream>
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../Sockets/includes/SocketHandler.hpp"
#include <memory>
#include <thread>
#include <condition_variable>
#include "../includes/ComCodes.hpp"
#include <chrono>
#include <unordered_map>
#include <queue>
#include "../../Core/Core.hpp"
#include "../../gameLoop/IGameLoop.hpp"
#include "../../gameLoop/RTypeGameLoop/RTypeGameLoop.hpp"
#include "../../EntityTypes/EntityTypes.hpp"
#include "../../Entity/Player.hpp"

namespace RType {
    namespace Server {
        /**
         * @brief base values for the room class
         * 
         */
        enum basesValues {
            ROOM_MAX_SIZE = 4,
            DESTROYED_NB_MSG_SEND = 5,
            CHECK_CRASHED_SECONDS = 3,
            CHECK_CRASHED_TIMES = 3,
        };
        /**
         * @brief class who controls one room
         * 
         */
        class Room {
            public:
                /**
                 * @brief Construct a new Room object
                 * 
                 * @param id id of the room
                 * @param maxSize number max of user in this room
                 * @param setSocket instance of the shared pointer of socketHandler
                 */
                Room(unsigned char id, unsigned char maxSize, std::shared_ptr<Utils::SocketHandler> setSocket, std::vector<std::map<Parser::Enemies, int>> waves);
                /**
                 * @brief Destroy the Room object
                 * 
                 */
                ~Room();
                /**
                 * @brief check if the room is full
                 * 
                 * @return true if the room is full
                 * @return false otherwise
                 */
                bool isFull() const;
                /**
                 * @brief add a new player to the room
                 * 
                 * @param toAdd new Player to add to the room
                 * @return true the player as been added to the team
                 * @return false otherwise
                 */
                bool addToRoom(const std::pair<std::string, int> &toAdd);
                /**
                 * @brief check if the user ToSearch is in room
                 * 
                 * @param toSearch player to search
                 * @return true if found
                 * @return false otherwise
                 */
                bool isInRoom(const std::pair<std::string, int> &toSearch) const;
                /**
                 * @brief send a message to a room
                 * 
                 * @param msg the message
                 * @return true if the user who need to get this message is in room
                 * @return false otherwise
                 */
                bool sendMessageToRoom(const Utils::MessageParsed_s &msg);
                /**
                 * @brief stop the room
                 * 
                 */
                void stopRoom();
                /**
                 * @brief Get the Id of the room
                 * 
                 * @return int id of the room
                 */
                unsigned char getId() const;
                /**
                 * @brief remove a player from a room
                 * 
                 * @param toRemove player to remove
                 * @return true if successfully removed 
                 * @return false otherwise
                 */
                bool removeFromRoom(const std::pair<std::string, int> &toRemove);
                /**
                 * @brief check if the room will be destroyed
                 * 
                 * @return true if the room will be destroyed
                 * @return false otherwise
                 */
                bool willBeDestroyed() const;
                /**
                 * @brief wait for the Room to be destroyed
                 * 
                 */
                void waitForDestroy();
                /**
                 * @brief Get the actual number of player of the room
                 * 
                 * @return int number of player
                 */
                int getNumberOfPlayer() const;
                /**
                 * @brief Get the Max Players of the room
                 * 
                 * @return int number of player
                 */
                int getMaxPlayers() const;
                /**
                 * @brief send a message to all the players of the room
                 * 
                 * @param msg the message to send
                 */
                void notifyAllPlayer(const Utils::MessageParsed_s &msg);
                /**
                 * @brief Set the willBeDestroy to true, so destroy the room
                 * 
                 */
                void setDestroy();
                /**
                 * @brief responds to a player who asked for his in game id
                 * 
                 * @param msg the message from the player
                 */
                void sendPlayerId(const Utils::MessageParsed_s &msg);
            private:
                /**
                 * @brief run the room inside of a thread, method launched at the constructor 
                 * 
                 */
                void runRoom();
                /**
                 * @brief function that send and receive ping of the players for check if they crashed or not
                 * 
                 */
                void checkCrashed();
                /**
                 * @brief handle of the ping message
                 * 
                 * @param msg the message received
                 */
                void messagePing(const Utils::MessageParsed_s &msg);
                /**
                 * @brief send the entity type of the id asked by a player
                 * 
                 * @param msg the message from the player
                 */
                void sendEntityType(const Utils::MessageParsed_s &msg);
                /**
                 * @brief Set the Enemies Waves in RTypeGameLoop
                 * 
                 * @param waves 
                 */
                void setEnemiesWaves(std::vector<std::map<Parser::Enemies, int>> waves);
                std::unique_ptr<std::thread> _roomThread;
                std::map<std::pair<std::string, int>, unsigned short> _allPlayers;
                std::map<std::pair<std::string, int>, bool> _playerOnline;
                std::shared_ptr<Utils::SocketHandler> _socket;
                std::mutex _mutex;
                bool _isOpen;
                Core _core;
                unsigned char _id;
                unsigned char _maxSize;
                bool _willBeDestroyed;
                unsigned char _actualPing;
                std::chrono::steady_clock::time_point _pingTime;
                std::unique_ptr<IGameLoop> _gameLoop;
                std::unique_ptr<std::mutex> _mutexQueue;
                std::unique_ptr<std::queue<std::pair<unsigned short, Utils::MessageParsed_s>>> _toSendToGameLoop;
                std::pair<std::string, int> _firstClient;

        };
    }
}
