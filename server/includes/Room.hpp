/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Room
*/

#pragma once
#include <vector>
#include <iostream>
#include "../../Sockets/includes/MessageParsed.hpp"
#include "../../Sockets/includes/SocketHandler.hpp"
#include <memory>
#include <thread>
#include <condition_variable>
#include "../includes/ComCodes.hpp"

#define ROOM_MAX_SIZE 4
#define DESTROYED_NB_MSG_SEND 5;

namespace RType {
    namespace Server {
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
                Room(unsigned char id, unsigned char maxSize, std::shared_ptr<Utils::SocketHandler> setSocket);
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
                int getId() const;
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
            private:
                /**
                 * @brief run the room inside of a thread, method launched at the constructor 
                 * 
                 */
                void runRoom();
                std::unique_ptr<std::thread> _roomThread;
                std::vector<std::pair<std::string, int>> _allPlayers;
                std::shared_ptr<Utils::SocketHandler> _socket;
                std::mutex _mutex;
                bool _isOpen;
                void *gameState;
                unsigned char _id;
                unsigned char _maxSize;
                bool _willBeDestroyed;
        };
    }
}
