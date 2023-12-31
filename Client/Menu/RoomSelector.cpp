/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomSelector
*/

#include "RoomSelector.hpp"

RType::RoomSelector::RoomSelector(std::function<void()> &createServer) :
_list("Assets/insanibu.ttf"),
_createServer(createServer),
_roomEditor(this->_sendedMessage, this->_messageToSend, this->_actualRoom)
{
    this->_openRoomEditor = false;
    this->_clock = std::chrono::steady_clock::now();
    this->_actualRoom = 0;
    this->_sendedMessage = true;
    this->_messageToSend.msgType = getListOfRooms;
    this->_list.addButtons([this]{
        this->_actualRoom = this->_currentRoomList.size() + 1;
        this->_openRoomEditor = true;
        // this->_messageToSend.msgType = newRoomIsCreated;
        // this->_messageToSend.bytes[0] = this->_actualRoom;
        // this->_sendedMessage = true;
        // std::cout << "clicked ???" << std::endl;
    }, 
    "Assets/buttonTest.png", "Create a \nnew room", sf::Vector2f(20.0, 20.0), sf::IntRect(0, 0, 150, 100), 100, 0);
        this->_list.addButtons([this]{
        this->_createServer();
        this->_actualRoom = this->_currentRoomList.size() + 1;
        this->_openRoomEditor = true;
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        // this->_actualRoom = this->_currentRoomList.size() + 1;
        // this->_messageToSend.msgType = newRoomIsCreated;
        // this->_messageToSend.bytes[0] = this->_actualRoom;
        // this->_sendedMessage = true;
        // // std::cout << "clicked ???" << std::endl;
    }, 
    "Assets/buttonTest.png", "Be the\nnew server", sf::Vector2f(1700.0, 20.0), sf::IntRect(0, 0, 150, 100), 100, 1);
}

void RType::RoomSelector::display(std::unique_ptr<sf::RenderWindow> &toDraw)
{
    if (this->_openRoomEditor)
        return this->_roomEditor.display(toDraw);
    auto clock = std::chrono::steady_clock::now();
    if (!this->_sendedMessage && std::chrono::duration_cast<std::chrono::milliseconds>(clock - this->_clock).count() > 100) {
        this->_clock = clock;
        this->_messageToSend.msgType = getListOfRooms;
        this->_sendedMessage = true;
    }
    this->_list.displayButtons(toDraw);
}

void RType::RoomSelector::hoverButtons(const sf::Vector2i &mousePos)
{
    if (this->_openRoomEditor)
        return this->_roomEditor.hoverButtons(mousePos);
    this->_list.hoverButtons(mousePos);
}

void RType::RoomSelector::clickedButtons(const sf::Vector2i &mousePos)
{
    if (this->_openRoomEditor)
        return this->_roomEditor.clickedButtons(mousePos);
    this->_list.clickButtons(mousePos);
}

void RType::RoomSelector::handleMessage(const Utils::MessageParsed_s &msg)
{
    if (msg.msgType != RType::listOfRooms)
        return;
    unsigned char roomId = msg.bytes[0];
    for (auto it : this->_currentRoomList)
        if (it == roomId)
            return;
    this->_list.addButtons([&, roomId]{
        this->_actualRoom = roomId;
        this->_messageToSend.msgType = newPlayerConnected;
        this->_messageToSend.bytes[0] = this->_actualRoom;
        this->_sendedMessage = true;
    }, 
    "Assets/buttonTest.png", "Room :" + std::to_string(static_cast<int>(roomId)) + "\n" + std::to_string(static_cast<int>(msg.bytes[1])) + " / " + std::to_string(static_cast<int>(msg.bytes[2])), 
    sf::Vector2f(20.0 + 110.0 * this->_currentRoomList.size(), 300.0), sf::IntRect(0, 0, 150, 100), 100, this->_currentRoomList.size() + 2);
    this->_currentRoomList.push_back(roomId);
}

RType::Utils::MessageParsed_s RType::RoomSelector::sendMessage()
{
    this->_sendedMessage = false;
    return this->_messageToSend;
}

bool RType::RoomSelector::needToSendMessage()
{
    return this->_sendedMessage;
}
