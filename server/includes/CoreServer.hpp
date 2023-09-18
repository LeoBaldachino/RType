/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Server
*/

#pragma once
#include "../../Sockets/includes/SocketServer.hpp"
#include <memory>
#include <exception>

namespace RType {
    class CoreServer {
        public:
            CoreServer(int, char **);
            ~CoreServer();
        private:
            void run();
            std::unique_ptr<Utils::SocketServer> _socket;
    };
}
