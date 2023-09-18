/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketServer
*/

#pragma once
#include "SocketHandler.hpp"

namespace RType {
    namespace Utils {
        class SocketServer : public SocketHandler {
            public:
                SocketServer(int port);
                ~SocketServer();
                void send(int to, MessageParsed_t &toSend);

            protected:
            private:
        };
    }
}