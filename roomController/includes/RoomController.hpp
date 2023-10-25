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
            void selectCommand(const std::string &command);
            void kickCommand(const std::string &command);
            void detailsCommand(const std::string &command);
            void helpCommand(const std::string &command);
            void showTeam(const Utils::MessageParsed_s &msg);
            void showTeamMembers(const Utils::MessageParsed_s &msg);
            void showPlayerDetails(const Utils::MessageParsed_s &msg);
            inline Utils::MessageParsed_s createEmptyMsg(ComCodes code) {unsigned char tab[7] = {0, 0, 0, 0, 0, 0, 0};return Utils::MessageParsed_s(code, this->_serverIp, this->_serverPort, tab);};
            std::unordered_map<unsigned char, void (RType::RoomController::*)(const Utils::MessageParsed_s &)> _commands;
            std::unordered_map<std::string, void (RType::RoomController::*)(const std::string &)> _lineCommands;
            std::unique_ptr<std::thread> _commandsThread;
            bool _threadOpen;
            std::string _serverIp;
            int _serverPort;
            std::shared_ptr<Utils::SocketHandler> _socket;
            std::mutex _mutex;
            unsigned short _actTeam;
    };
}
