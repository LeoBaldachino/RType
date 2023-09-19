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
                SocketHandler(const std::string &ipAdress, int port);
                ~SocketHandler();
                template<typename T>
                void send(const struct MessageParsed_s<T> &toSend, const std::string &ipAdress, int port);
                template<typename T, typename R>
                MessageParsed_s<R> receive(T &toPass);
            protected:
                boost::asio::io_service _ioService;
                boost::asio::ip::udp::socket _socket;
                boost::asio::ip::udp::endpoint _Endpoint;
                template<typename T, typename R>
                void handleReceive(const boost::system::error_code& error, size_t bytes_transferred, T &toPass);
        };
    }
}
