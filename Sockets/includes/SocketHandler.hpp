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
        /**
         * @brief class socketHandler, class used for handle the sockets, use the asio library and it's an singleton
         * 
         */
        class SocketHandler {
            public:
                /**
                 * @brief Construct a new Socket Handler object
                 * 
                 * @param ipAdress
                 * @param port 
                 */
                SocketHandler(const std::string &ipAdress, int port);
                /**
                 * @brief copy constructor of the socketHandler
                 * 
                 * @param socket socket to copy
                 */
                SocketHandler(const SocketHandler &socket);
                /**
                 * @brief Destroy the Socket Handler object
                 * 
                 */
                ~SocketHandler();
                /**
                 * @brief send a message the user resigned in the message
                 * 
                 * @param toSend message to send
                 */
                void send(const struct MessageParsed_s &toSend);
                /**
                 * @brief receive a message, blocking function
                 * 
                 * @return MessageParsed_s message received
                 */
                MessageParsed_s receive();
                /**
                 * @brief Get the Instance object singleton
                 * 
                 * @return std::shared_ptr<SocketHandler> the instance
                 */
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
