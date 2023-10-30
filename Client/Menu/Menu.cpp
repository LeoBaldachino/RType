/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Menu
*/

#include "Menu.hpp"

RType::Menu::Menu(PopUp &popUp, std::function<void()> fn) :
_popUp(popUp),
_roomSelector(fn)
{
    this->_text.loadFromFile("../Assets/background_game_real.png");
    this->_sprite.setTexture(this->_text);
    this->_panel = baseMenu;
    this->_closeMenu = false;
}

RType::Menu::~Menu()
{
}


void RType::Menu::displayMenu(std::unique_ptr<sf::RenderWindow> &window, bool mouseClicked)
{
    // std::cout << "Start display menu" << std::endl;
    window->draw(this->_sprite);
    auto mousePos = sf::Mouse::getPosition(*window);
    if (this->_panel == loadingScreen)
        std::cout << "Loading screen..." << std::endl;
    if (this->_panel == roomSelector) {
        // std::cout << "Room selector ?" << std::endl;
        mouseClicked ? this->_roomSelector.clickedButtons(mousePos) : this->_roomSelector.hoverButtons(mousePos);
        if (!this->_messagesQueue.empty()) {
            this->_roomSelector.handleMessage(this->_messagesQueue.front());
            this->_messagesQueue.pop();
        }
        if (this->_roomSelector.needToSendMessage()) {
            std::cout << "need to send message" << std::endl;
            this->_toSend.push(this->_roomSelector.sendMessage());
        }
        this->_roomSelector.display(window);
        // std::cout << "Room selector end ?" << std::endl;
    }
    if (this->_panel == baseMenu) {
        // std::cout << "base menu" << std::endl;
        this->_baseMenu.display(window);
        // std::cout << "disp base menu" << std::endl;
        mouseClicked ? this->_baseMenu.clickedButtons(mousePos) : this->_baseMenu.hoverButtons(mousePos);
        // std::cout << "mouse click menu" << std::endl;
        if (this->_baseMenu.exited())
            this->_panel = roomSelector;
    }
    // std::cout << "End display menu" << std::endl;
}

void RType::Menu::addMessage(const Utils::MessageParsed_s &msg)
{
    if (msg.msgType > 0 && msg.msgType < 20) {
        this->_closeMenu = true;
        return;
    }
    this->_messagesQueue.push(msg);
}