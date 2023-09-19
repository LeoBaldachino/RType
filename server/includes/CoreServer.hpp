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
#include <unordered_map>

namespace RType {
    class CoreServer {
        public:
            CoreServer(int, char **);
            ~CoreServer();
        private:
            void run();
            void sendInfosThread();
            void threadMethod(RType::Utils::MessageParsed_s);
            std::unique_ptr<Server::ThreadPool> _threadPool;
            std::unique_ptr<Utils::SocketHandler> _socket;
            std::unique_ptr<std::thread> _senderThread;
            std::mutex _mutex;
            std::unordered_map<char, std::pair<std::string, int>> _clients;
    };
}
