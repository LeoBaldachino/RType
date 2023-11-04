/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** RoomEditor
*/

#include "RoomEditor.hpp"

// 
RType::RoomEditor::RoomEditor(bool &sendMsg, Utils::MessageParsed_s &msg, int &sizeNb) :
_msg(msg),
_sendMsg(sendMsg),
_list("../Assets/insanibu.ttf"),
_sizeNb(sizeNb)
{
    this->_posLife = sf::Vector2f(800.0, 490.0);
    this->_posNbPlayer = sf::Vector2f(300.0, 490.0);
    this->_nbOfPlayers = 4;
    this->_baseLifePlayer = 3;
    this->_list.addButtons([this]{
        this->_nbOfPlayers++;
    }, 
    "../Assets/buttonTest.png", "+", sf::Vector2f(300.0, 270.0), sf::IntRect(0, 0, 150, 100), 100, 0);
    this->_list.addButtons([this]{
        if (this->_nbOfPlayers < 2)
            return;
        this->_nbOfPlayers--;
    }, 
    "../Assets/buttonTest.png", "-", sf::Vector2f(300.0, 670.0), sf::IntRect(0, 0, 150, 100), 100, 1);
    this->_list.addButtons([this]{
        this->_baseLifePlayer++;
    }, 
    "../Assets/buttonTest.png", "+", sf::Vector2f(800.0, 270.0), sf::IntRect(0, 0, 150, 100), 100, 2);
    this->_list.addButtons([this]{
        if (this->_baseLifePlayer < 2)
            return;
        this->_baseLifePlayer--;
    }, 
    "../Assets/buttonTest.png", "-", sf::Vector2f(800.0, 670.0), sf::IntRect(0, 0, 150, 100), 100, 3);
    this->_list.addButtons([this] {
        this->_sendMsg = true;
        this->_msg.msgType = newRoomIsCreated;
        this->_msg.bytes[0] = static_cast<unsigned char>(this->_sizeNb);
        this->_msg.bytes[1] = this->_nbOfPlayers;
        this->_msg.bytes[2] = this->_baseLifePlayer;
    }, 
    "../Assets/buttonTest.png", "Ajouter une salle", sf::Vector2f(440.0, 850.0), sf::IntRect(0, 0, 150, 100), 100, 4);
    this->_font = this->_list.getFont();
    this->_text.setFont(this->_font);
}

RType::RoomEditor::~RoomEditor()
{
}

void RType::RoomEditor::display(std::unique_ptr<sf::RenderWindow> &toDraw)
{
    this->_text.setPosition(this->_posLife);
    this->_text.setString(std::to_string(static_cast<int>(this->_baseLifePlayer)));
    toDraw->draw(this->_text);
    this->_text.setPosition(this->_posNbPlayer);
    this->_text.setString(std::to_string(static_cast<int>(this->_nbOfPlayers)));
    toDraw->draw(this->_text);
    this->_list.displayButtons(toDraw);
}