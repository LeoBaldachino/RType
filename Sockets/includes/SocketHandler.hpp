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
#include <tuple>
#include <mutex>

namespace RType {
    namespace Utils {
        class SocketHandler {
            public:
            /**
             * @brief Construct a new Socket Handler object
             * 
             * @param ipAdress
             * @param port 
             */
                SocketHandler(const std::string &ipAdress, int port);
                ~SocketHandler();
                void send(const struct MessageParsed_s &toSend);
                MessageParsed_s receive();
                const std::unique_ptr<SocketHandler> &getInstance() const;
            protected:
                boost::asio::io_service _ioService;
                boost::asio::ip::udp::socket _socket;
                boost::asio::ip::udp::endpoint _Endpoint;
                std::unique_ptr<SocketHandler> _instance;
                std::mutex _mutex;
        };
    }
}
