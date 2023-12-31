/**
 * @file Client.hpp
 * @author EPITECH PROJECT, 2023
 * @brief Client class definition
 */

#pragma once
#include "Texture/Texture.hpp"
#include "Parallax/Parallax.hpp"
#include "Parallax/ParallaxGnome.hpp"
#include "Parallax/ParallaxDragon.hpp"
#include "../ECS/Entity/Player.hpp"
#include "../Core/Core.hpp"
#include "../EntityTypes/EntityTypes.hpp"
#include "../Visitor/SystemVisitor.hpp"
#include "../Sockets/includes/SocketHandler.hpp"
#include "../Sockets/includes/MessageParsed.hpp"
#include "../server/includes/ComCodes.hpp"
#include "LifeBar/LifeBar.hpp"
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "Prediction/Prediction.hpp"
#include "Button/ButtonList.hpp"
#include "Menu/Menu.hpp"
#include "PopUp/PopUp.hpp"
#include "MessagePanel/MessagePanel.hpp"
#include "Hud/Hud.hpp"
#include "SoundPlayer/SoundPlayer.hpp"
#include "ClientEncaps.hpp"

#define GET_ID_LIMIT_TIME 1

namespace RType {
    /**
     * @class Client
     * @brief Class representing a client in the RType game
     */
    class Client {
        public:
            /**
             * @enum Events
             * @brief Enum representing possible events in the game
             */


            enum Screens {
                menu,
                game,
                serverDisconnected,
                gameOver
            };
            /**
             * @brief Construct a new Client object
             * @param ac Argument count
             * @param av Argument vector
             */
            Client(int ac, char **av);

            /**
             * @brief Destroy the Client object
             */
            ~Client() {};

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
            void newCoin(const Utils::MessageParsed_s &msg);
            void newGenie(const Utils::MessageParsed_s &msg);
            void newDragon(const Utils::MessageParsed_s &msg);
            void newDragonShot(const Utils::MessageParsed_s &msg);
            void newGenieShot(const Utils::MessageParsed_s &msg);
            void newMermaid(const Utils::MessageParsed_s &msg);
            void newMermaidShot(const Utils::MessageParsed_s &msg);
            void newTourreToRoom(const Utils::MessageParsed_s &msg);
            void removeAnEntity(const Utils::MessageParsed_s &msg);
            void newBydosShoot(const Utils::MessageParsed_s &msg);
            void setValues(const Utils::MessageParsed_s &msg);
            void newMyShoot(const Utils::MessageParsed_s &msg);
            void newPercingShoot(const Utils::MessageParsed_s &msg);
            void newMessage(const Utils::MessageParsed_s &msg);
            void gameLoop();
            void changeTypeEntityAndMove(const Utils::MessageParsed_s &msg, std::unordered_map<unsigned short, std::shared_ptr<IEntity>>::iterator &it);
            sf::Sprite getSpriteFromEntity(std::shared_ptr<IEntity> entity, unsigned int id);
            void sendInputs();
            void syncNbOfEntities(const Utils::MessageParsed_s &msg);
            void setLifeBars();
            void displayMenu();
            void quitActualRoom();
            void setRoomDetails(const Utils::MessageParsed_s &msg);
            std::unique_ptr<std::thread> _infosThread;
            std::shared_ptr<Utils::SocketHandler> _socket;
            std::unique_ptr<sf::RenderWindow> _window;
            SystemVisitor _visitor;
            Core _entities;
            Core _predictionCore;
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
            std::unique_ptr<LifeBar> _lifeBar;
            sf::Music _music;
            Screens _actualScreen;
            bool _gameAsStarted;
            Texture _texture;
            std::unique_ptr<Prediction> _predicate;
            ButtonList _buttonList;
            bool _mouseClicked;
            Parallax _parallax;
            ParallaxGnome _parallaxGnome;
            ParallaxDragon _parallaxDragon;
            Menu _menu;
            unsigned int _level = 0;
            bool roomDetailsSet = false;
            PopUp _popUp;
            bool _quittedRoom = false;
            int _serverPid;
            MessagePanel _msgPanel;
            Hud _hud;
            SoundPlayer _soundPlayer;
            int _currentMusic = -1;
            int _currentParralax = -1;
            ClientEncaps _encaps;
    };
}
