/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Server
*/

#pragma once
#include "../../Sockets/includes/SocketHandler.hpp"
#include "../../Sockets/includes/MessageParsed.hpp"
#include "Parser.hpp"
#include "ThreadPool.hpp"
#include <memory>
#include <exception>
#include <chrono>
#include "Room.hpp"

namespace RType {
    /**
     * @brief core class of the server, allows you to connect together the socket and the ecs
     * 
     */
    class CoreServer {
        public:
            /**
             * @brief Construct a new Core Server object
             * 
             * @param ar first param of the main function
             * @param av the second param of the main function
             */
            CoreServer(int ac, char **av);
            /**
             * @brief Destroy the Core Server object
             * 
             */
            ~CoreServer();
        private:
            /**
             * @brief run the Server, this function is called when the server object is created
             * 
             */
            void run();
            /**
             * @brief the method used by the thread pool each time a new message is receive
             * 
             * @param msg the message received
             */
            void threadMethod(const RType::Utils::MessageParsed_s &msg);
            /**
             * @brief send the list of room to the user who asked
             * 
             * @param msg the message received
             */
            void getRoomList(const RType::Utils::MessageParsed_s &msg);
            /**
             * @brief create a new room when asked
             * 
             * @param msg the message received
             */
            void newRoomCreated(const RType::Utils::MessageParsed_s &msg);
            /**
             * @brief remove the player from a room
             * 
             * @param msg the message received
             */
            void getOutFromRoom(const RType::Utils::MessageParsed_s &msg);
            /**
             * @brief connect a player to a room
             * 
             * @param msg the message received
             */
            void connectToRoom(const RType::Utils::MessageParsed_s &msg);
            std::unique_ptr<Server::ThreadPool> _threadPool;
            std::unique_ptr<Utils::SocketHandler> _socket;
            std::mutex _mutex;
            std::vector<std::pair<std::string, int>> _clients;
            std::vector<std::unique_ptr<Server::Room>> _rooms;
    };
}
