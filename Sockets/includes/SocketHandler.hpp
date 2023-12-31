/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** SocketHandler.hpp
*/

#pragma once
#include <asio.hpp>
#include "MessageParsed.hpp"
#include <tuple>
#include <mutex>
#include <thread>
#include "MessageSendedQueue.hpp"
#include "PacketTracker.hpp"

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
                SocketHandler(const std::string &ipAdress, int port, const std::list<int> &importantMessagesCode);
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
            private:
                void send();
                void senderThread();
                asio::io_service _ioService;
                std::shared_ptr<asio::ip::udp::socket> _socket;
                asio::ip::udp::endpoint _Endpoint;
                std::shared_ptr<SocketHandler> _instance;
                std::shared_ptr<std::mutex> _mutex;
                std::shared_ptr<std::mutex> _receiverMutex;
                std::shared_ptr<MessageSendedQueue> _queueMsg;
                std::pair<std::string, int> _ipPort;
                std::shared_ptr<PacketTracker> _packetTracker;
                std::shared_ptr<std::thread> _senderThread;
                std::shared_ptr<bool> _threadOpen;
        };
    }
}
