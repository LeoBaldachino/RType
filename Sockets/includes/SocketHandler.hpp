/**
 * @file SocketHandler.hpp
 * @brief SocketHandler class definition
 * 
 * This file contains the SocketHandler class which is used to manage the socket connections.
 * 
 * @author EPITECH PROJECT, 2023
 * @version B-CPP-500-MLH-5-1-rtype-robin.denni
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
         * @class SocketHandler
         * @brief Class to manage the socket connections
         * 
         * This class is used to manage the socket connections.
         */
        class SocketHandler {
            public:
            /**
             * @brief Construct a new Socket Handler object
             * 
             * @param ipAdress The IP address to connect to
             * @param port The port to connect to
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
                /**
                 * @brief Get the Ip And Port 
                 * 
                 * @return const std::pair<std::string, int> ip, port
                 */
                const std::pair<std::string, int> &getIpAndPort() const;
            protected:
                boost::asio::io_service _ioService;
                std::shared_ptr<boost::asio::ip::udp::socket> _socket;
                boost::asio::ip::udp::endpoint _Endpoint;
                std::shared_ptr<SocketHandler> _instance;
                std::shared_ptr<std::mutex> _mutex;
                std::shared_ptr<std::mutex> _receiverMutex;
                std::pair<std::string, int> _ipPort;
        };
    }
}
