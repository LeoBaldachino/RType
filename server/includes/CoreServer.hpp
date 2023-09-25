/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Server
*/

#pragma once
#include "../../Sockets/includes/SocketHandler.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "ThreadPool.hpp"
#include <memory>
#include <exception>
#include <chrono>
#include "Room.hpp"

namespace RType {
    class CoreServer {
        public:
            CoreServer(int, char **);
            ~CoreServer();
        private:
            void run();
            void threadMethod(const RType::Utils::MessageParsed_s &);
            void getRoomList(const RType::Utils::MessageParsed_s &);
            void newRoomCreated(const RType::Utils::MessageParsed_s &);
            void getOutFromRoom(const RType::Utils::MessageParsed_s &);
            void connectToRoom(const RType::Utils::MessageParsed_s &);
            std::unique_ptr<Server::ThreadPool> _threadPool;
            std::unique_ptr<Utils::SocketHandler> _socket;
            std::mutex _mutex;
            std::vector<std::pair<std::string, int>> _clients;
            std::vector<std::unique_ptr<Server::Room>> _rooms;
    };
}
