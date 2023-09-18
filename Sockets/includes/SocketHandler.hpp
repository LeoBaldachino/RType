/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler
*/

#pragma once
#include <boost/asio.hpp>

namespace RType {
    namespace Utils {
        class SocketHandler {
            public:
                SocketHandler(int port);
                ~SocketHandler();
                void send(const void *data, size_t dataSize);
                const void *receive(int timeout);
            protected:
            private:
        };
    }
}
