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

#define ROOM_MAX_SIZE 4

namespace RType {
    namespace Server {
        class Room {
            public:
                /**
                 * @brief Construct a new Room object
                 * 
                 * @param id 
                 * @param maxSize
                 */
                Room(unsigned char id, unsigned char maxSize, std::unique_ptr<Utils::SocketHandler> &setSocket);
                ~Room();
                bool isFull() const;
                bool addToRoom(const std::pair<std::string, int> &toAdd);
                bool isInRoom(const std::pair<std::string, int> &toSearch) const;
                bool sendMessageToRoom(const Utils::MessageParsed_s &msg);
                void stopRoom();
                int getId() const;
                bool removeFromRoom(const std::pair<std::string, int> &toRemove);
            private:
                void runRoom();
                std::unique_ptr<std::thread> _roomThread;
                std::vector<std::pair<std::string, int>> _allPlayers;
                std::unique_ptr<Utils::SocketHandler> &_socket;
                std::mutex _mutex;
                bool _isOpen;
                void *gameState;
                unsigned char _id;
                unsigned char _maxSize;
        };
    }
}
