/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomController
*/

#include "../includes/RoomController.hpp"

RType::RoomController::RoomController(int ac, char **av) :
_lineCommands({
    {"ls", &RType::RoomController::lsCommand},
    {"select", &RType::RoomController::selectCommand},
    {"kick", &RType::RoomController::kickCommand},
    {"details ", &RType::RoomController::detailsCommand},
    {"help", &RType::RoomController::helpCommand},
}),
_commands({
    {listOfRooms, &RType::RoomController::showTeam},
    {sendRoomMembers, &RType::RoomController::showTeamMembers},
})
{
    if (ac != 3)
        throw std::invalid_argument("Not enougth arguments");
    this->_serverIp = av[1];
    this->_actTeam = 0;
    this->_serverPort = std::stoi(std::string(av[2]));
    this->_threadOpen = true;
    this->_socket = std::make_unique<Utils::SocketHandler>("127.0.0.1", 4001 + std::rand() % 3000, std::list<int>({keyPressed, entityType, playerPing, newPlayerConnected, givePlayerId, destroyedRoom, serverStop, entityType, removeEntity, playerDeconnected, newRoomIsCreated, playerGetId, givePlayerId}));
    this->_commandsThread = std::make_unique<std::thread>(&RType::RoomController::launchGetter, this);
    this->run();
}

RType::RoomController::~RoomController()
{
    this->_threadOpen = false;
    this->_commandsThread->join();
}

void RType::RoomController::launchGetter()
{
    while (this->_threadOpen) {
        auto msg = this->_socket->receive();
        auto it = this->_commands.find(msg.msgType);
        if (it == this->_commands.end()) {
            std::cout << "Get an unhandled message " << static_cast<int>(msg.msgType) << std::endl;
            continue;
        }
        (this->*it->second)(msg);
    }
}

void RType::RoomController::run()
{
    while (true) {
        std::string actual_line;
        if (!std::getline(std::cin, actual_line, '\n'))
            return;
        std::string actLineStart;
        for (auto i : actual_line)
            if (i == ' ' || i == '\n')
                break;
            else
                actLineStart.push_back(i);
        auto it = this->_lineCommands.find(actLineStart);
        if (it == this->_lineCommands.end()) {
            std::cout << "Don't know the command '" << actual_line << "' try help" << std::endl;
            continue;
        }
        actual_line.erase(0, it->first.size());
        (this->*it->second)(actual_line);
    }
}

void RType::RoomController::lsCommand(const std::string &command)
{
    (void)command;
    if (!this->_actTeam) {
        Utils::MessageParsed_s msg = this->createEmptyMsg(getListOfRooms);
        this->_socket->send(msg);
        return;
    }
    Utils::MessageParsed_s msg = this->createEmptyMsg(getRoomMembers);
    msg.setFirstShort(this->_actTeam);
    this->_socket->send(msg);
}

void RType::RoomController::selectCommand(const std::string &command)
{
    if (command == "..") {
        this->_actTeam = 0;
        return;
    }
    unsigned short roomId;
    try {
        roomId = std::stoi(command);
    } catch (const std::exception &err) {
        std::cout << "Invalid room number..." << std::endl;
        return;
    }
    this->_actTeam = roomId;
}

void RType::RoomController::kickCommand(const std::string &command)
{
    if (!this->_actTeam) {
        std::cout << "No room selected..." << std::endl;
        return;
    }
}

void RType::RoomController::detailsCommand(const std::string &command)
{
    if (!this->_actTeam) {
        std::cout << "No room selected..." << std::endl;
        return;
    }
}

void RType::RoomController::helpCommand(const std::string &command)
{
    (void)command;
    std::cout << "\nCommands :\n\nls : get the current rooms, get the list of player if the scope is set to a room\n\nselect [ARGUMENT]: change the scope of the controller, precise a room number for get the scope of this room, precise .. for comeback in initial scope\n\n"
    "kick [ARGUMENT] : kick a player from the room, you MUST have your scope set to this room and precise a player id\n\ndetails [ARGUMENT] : get details about a player in a room, you MUST have your scope set to this room and precise the player id\n\nhelp : this help" << std::endl;
}

void RType::RoomController::showTeam(const Utils::MessageParsed_s &msg)
{
    std::cout << "Room number " << static_cast<int>(msg.bytes[0]) << " status " << static_cast<int>(msg.bytes[1]) << "/" << static_cast<int>(msg.bytes[2]) << std::endl;
}

void RType::RoomController::showTeamMembers(const Utils::MessageParsed_s &msg)
{
    std::cout << "Members of the team " << this->_actTeam << ":\n\n";
    for (unsigned char i = 0; i < 7; ++i) {
        if (msg.bytes[i] == 255)
            break;
        std::cout << "Player id = " << static_cast<int>(msg.bytes[i]) << "\n";
    }
    std::cout << std::endl;
}