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
                SocketHandler(const SocketHandler &socket);
                ~SocketHandler();
                void send(const struct MessageParsed_s &toSend);
                MessageParsed_s receive();
                std::shared_ptr<SocketHandler> getInstance() const;
            protected:
                boost::asio::io_service _ioService;
                std::shared_ptr<boost::asio::ip::udp::socket> _socket;
                boost::asio::ip::udp::endpoint _Endpoint;
                std::shared_ptr<SocketHandler> _instance;
                std::shared_ptr<std::mutex> _mutex;
        };
    }
}
