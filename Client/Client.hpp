/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Client
*/

#pragma once
#include "../Entity/Player.hpp"
#include "../Visitor/SystemVisitor.hpp"
#include "../Sockets/includes/SocketHandler.hpp"
#include "../Sockets/includes/MessageParsed.hpp"
#include "../server/includes/ComCodes.hpp"
#include <unordered_map>
#include "../Core/Core.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#define GET_ID_LIMIT_TIME 500

namespace RType {
    class Client {
        public:
            enum Events {
                Up,
                Down,
                Left,
                Right,
                Shoot,
                PiercingShoot,
                CloseWindow,
                Unknown
            };
            Client(int ac, char **av);
            ~Client();
        private:
            void run();
            void infosThread();
            void createRoom(unsigned char roomNb);
            void joinRoom(unsigned char roomNb);
            void sendPing(const Utils::MessageParsed_s &msg);
            void handleNonAuthorized(const Utils::MessageParsed_s &msg);
            Utils::MessageParsed_s buildEmptyMsg(const RType::ComCodes &code);
            void newPlayerToRoom(const Utils::MessageParsed_s &msg);
            void getNewId(const Utils::MessageParsed_s &msg);
            void moveEntity(const Utils::MessageParsed_s &msg);
            bool checkAsId();
            void quitRoom(const Utils::MessageParsed_s &msg);
            void serverStopped(const Utils::MessageParsed_s &msg);
            void getEntityType(unsigned short id);
            void setEntityType(const Utils::MessageParsed_s &msg);
            void handleInputs(void);
            void updateInputs(void);
            void newBydosToRoom(const Utils::MessageParsed_s &msg);
            void removeAnEntity(const Utils::MessageParsed_s &msg);
            void newEnemyShoot(const Utils::MessageParsed_s &msg);
            void setValues(const Utils::MessageParsed_s &msg);
            void newMyShoot(const Utils::MessageParsed_s &msg);
            void newPercingShoot(const Utils::MessageParsed_s &msg);
            std::unique_ptr<std::thread> _infosThread;
            std::shared_ptr<Utils::SocketHandler> _socket;
            std::unique_ptr<sf::RenderWindow> _window;
            SystemVisitor _visitor;
            Core _entities;
            std::unique_ptr<std::mutex> _mutex;
            std::string _serverIp;
            int _serverPort;
            bool _threadIsOpen;
            unsigned char _actualRoom;
            std::unordered_map<int, void (RType::Client::*)(const Utils::MessageParsed_s &)> _commands;
            int _actualId;
            std::unordered_map<Events, bool> _keysDown;
            bool shooting = false;
            std::chrono::steady_clock::time_point shotTime;
            std::vector<Events> _inputs;
            std::chrono::steady_clock::time_point _sendInputTime;
            std::unordered_map<unsigned short, std::chrono::steady_clock::time_point> _getIdLimiters;
    };
}
