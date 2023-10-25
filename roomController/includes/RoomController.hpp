/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomController
*/

#pragma once
#include "../../Sockets/includes/SocketHandler.hpp"
#include "../../server/includes/ComCodes.hpp"

#include <unordered_map>

namespace RType {
    class RoomController {
        public:
            RoomController(int ac, char **av);
            ~RoomController();
        private:
            void launchGetter();
            void run();
            void lsCommand(const std::string &command);
            std::unordered_map<unsigned char, void (RType::RoomController::*)(const Utils::MessageParsed_s &)> _commands;
            std::unordered_map<std::string, void (RType::RoomController::*)(const std::string &)> _lineCommands;
            std::unique_ptr<std::thread> _commandsThread;
            bool _threadOpen;
            std::string _serverIp;
            int _serverPort;
            std::shared_ptr<Utils::SocketHandler> _socket;
            std::mutex _mutex;
    };
}
