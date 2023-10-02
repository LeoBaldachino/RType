/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Client
*/

#include "Client.hpp"

RType::Client::Client(int ac, char **av) : 
_commands({
{(playerPing), &RType::Client::sendPing},
{illegalAction, &RType::Client::handleNonAuthorized},
{newPlayerConnected, &RType::Client::newPlayerToRoom},
{givePlayerId, &RType::Client::newPlayerToRoom},
})
{
    std::srand(std::time(NULL));
    if (ac < 3)
        throw std::invalid_argument("Not enought arguments");
    this->_serverIp = av[1];
    this->_serverPort = std::stoi(av[2]);
    this->_mutex = std::make_unique<std::mutex>();
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type");
    this->_socket = std::make_unique<Utils::SocketHandler>("127.0.0.1", 4001 + std::rand() % 3000);
    this->_threadIsOpen = true;
    this->_actualId = 0;
    this->_infosThread = std::make_unique<std::thread>(&RType::Client::infosThread, this);
    this->run();
}

RType::Client::~Client()
{
}

void RType::Client::run()
{
    this->createRoom(1);
    while (_window->isOpen()) {
        _window->clear();
        for (auto &it : this->_entities._entities)
            it.second->accept(this->_visitor, _window);
        _window->display();
    }
}

void RType::Client::infosThread()
{
    while (this->_threadIsOpen) {
        std::cout << "Ready to take some messages !" << std::endl;
        Utils::MessageParsed_s msg = this->_socket->receive();
        std::cout << "Receive message " << static_cast<int>(msg.msgType) << std::endl;
        auto it = this->_commands.find(msg.msgType);
        if (it == this->_commands.end()) {
            std::cout << "Get an unhandled message " << static_cast<int>(msg.msgType) << std::endl;
            continue;
        }
        (this->*it->second)(msg);
    }
}

void RType::Client::sendPing(const Utils::MessageParsed_s &recMsg)
{
    auto msg = this->buildEmptyMsg(playerPing);
    this->_socket->send(msg);
    std::cout << "Ping sended..." << std::endl;
}


void RType::Client::handleNonAuthorized(const Utils::MessageParsed_s &msg)
{
    if (msg.bytes[2] == newRoomIsCreated) {
        this->_mutex->lock();
        this->_actualRoom = 0;
        this->_mutex->unlock();
        return this->joinRoom(1);
    }
    std::cout << "Unauthorized " << static_cast<int>(msg.bytes[0]) << std::endl;
}

RType::Utils::MessageParsed_s RType::Client::buildEmptyMsg(const ComCodes &code)
{
    Utils::MessageParsed_s msg;
    msg.msgType = code;
    msg.senderIp = this->_serverIp;
    msg.senderPort = this->_serverPort;
    return msg;
}

void RType::Client::joinRoom(unsigned char roomNb)
{
    Utils::MessageParsed_s msg = this->buildEmptyMsg(newPlayerConnected);
    msg.bytes[0] = roomNb;
    this->_socket->send(msg);
    std::unique_lock<std::mutex>(*this->_mutex);
    this->_actualRoom = 1;
}

void RType::Client::createRoom(unsigned char roomNb)
{
    Utils::MessageParsed_s msg = this->buildEmptyMsg(newRoomIsCreated);
    msg.bytes[0] = roomNb;
    this->_socket->send(msg);
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_actualRoom = 1;
    this->_entities.addEntity(std::make_shared<Player>(Position(0, 0, 1080, 1920)), 0);
}

void RType::Client::newPlayerToRoom(const Utils::MessageParsed_s &msg)
{
    std::cout << "New player connected !!" << std::endl;
    this->_entities.addEntity(std::make_shared<Player>(Position(0, 0, 1080, 1920)), msg.getFirstShort());
    //todo -> store the player id for know wich one is moving
}

void RType::Client::getNewId(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_actualId = msg.getFirstShort();
    auto find = this->_entities._entities.find(0);
    auto ptrFind = find->second;
    this->_entities._entities.erase(find);
    this->_entities.addEntity(ptrFind, this->_actualId);
}


/*

quand système d'id sera fonctionnel, utiliser cette fonction tant que le client n'a pas reçu d'id et ne faire aucune action
si le client n'a pas d'id pour ne pas faire d'erreurs

idem pour toutes les entitées -> tant qu'on ne sait pas qui elles sont continuer à demander et ne pas faire d'action sur elles

*/
bool RType::Client::checkAsId()
{
    if (this->_actualId != 0)
        return true;
    auto msg = this->buildEmptyMsg(playerGetId);
    this->_socket->send(msg);
    return false;
}