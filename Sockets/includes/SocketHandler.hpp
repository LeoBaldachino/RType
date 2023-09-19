/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler
*/

#pragma once
#include <boost/asio.hpp>
#include "MessageParsed.hpp"
#include <boost/array.hpp>

namespace RType {
    namespace Utils {
        class SocketHandler {
            public:
                SocketHandler(const std::string &ipAdress, int port);
                ~SocketHandler();
                void send(const struct MessageParsed_s &toSend, const std::string &ipAdress, int port);
                MessageParsed_s receive();
            protected:
                boost::asio::io_service _ioService;
                boost::asio::ip::udp::socket _socket;
                boost::asio::ip::udp::endpoint _Endpoint;
        };
    }
}
