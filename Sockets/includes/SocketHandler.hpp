/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler
*/

#pragma once
#include <boost/asio.hpp>
#include "MessageParsed.hpp"

namespace RType {
    namespace Utils {
        class SocketHandler {
            public:
                SocketHandler(int port);
                ~SocketHandler();
                void send(const MessageParsed_t &toSend);
                MessageParsed_t receive(int timeout);
            protected:
                boost::asio::io_service _ioService;
                boost::asio::ip::udp::socket _socket;
                boost::asio::ip::udp::endpoint _Endpoint;
        };
    }
}
