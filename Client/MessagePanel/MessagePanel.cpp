/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MessagePanel
*/

#include "MessagePanel.hpp"

RType::MessagePanel::MessagePanel() : _list("../Assets/insanibu.ttf")
{
    this->_font = this->_list.getFont();
    this->_alltexts = {"Hello", "Bydos", "Boss", "Morning", "Vision", "I'm", "of", "over there", "Happiness", "Coin", "Need", "...", "!", "Warning", "Danger", "Genuis",
    "Happy", "To", "With", "You", "Are", "Usefull", "Wish", "Luck", "Tourre", "A", "Full", "In", "Life", "I", "Lack", ".", "?", "World", "Cup", "Amazing", "Chest", "Ahead"};
    std::sort(this->_alltexts.begin(), this->_alltexts.end());
    this->_globText.setPosition(sf::Vector2f(20.0, 850.0));
    this->_globText.setFont(this->_font);
    sf::Vector2f pos(100.0, 10.0);
    int cp = 0;
    for (auto it : this->_alltexts) {
        this->_list.addButtons([this, cp, it]{if (this->_message.size() > 6) return;this->_message.push_back(cp);this->_messageText.push_back(it);}, "../Assets/buttonTest.png", it, pos, sf::IntRect(0, 0, 150, 100), 100, cp);
        pos.x += 150.0;
        if (pos.x >= 1600.0) {
            pos.x = 10.0;
            pos.y += 180.0;
        }
        ++cp;
    }
    this->_list.addButtons([this]{if (this->_message.size() < 1) return;this->_message.pop_back();this->_messageText.pop_back();}, "../Assets/buttonTest.png", "<--", sf::Vector2f(20.0, 920.0), sf::IntRect(0, 0, 150, 100), 100, cp);
    ++cp;
    this->_list.addButtons([this]{this->_readyToSend = true;}, "../Assets/buttonTest.png", "Send", sf::Vector2f(190.0, 920.0), sf::IntRect(0, 0, 150, 100), 100, cp);
}

RType::Utils::MessageParsed_s RType::MessagePanel::sendMessage()
{
    RType::Utils::MessageParsed_s msg;
    msg.msgType = message;
    for (int i = 0; i < 7; ++i)
        msg.bytes[i] = 0;
    int cp = 0;
    for (auto it : this->_message) {
        if (cp >= 7)
            break;
        msg.bytes[cp] = it +1;
        cp++;
    }
    this->_message.clear();
    this->_messageText.clear();
    return msg;
}

void RType::MessagePanel::hoverButtons(const sf::Vector2i &mousePos)
{
    this->_list.hoverButtons(mousePos);
}

void RType::MessagePanel::clickButtons(const sf::Vector2i &mousePos)
{
    this->_list.clickButtons(mousePos);
}

void RType::MessagePanel::display(std::unique_ptr<sf::RenderWindow> &window)
{
    if (!this->_isOpen)
        return;
    std::string actMsg = "";
    for (auto it : this->_messageText)
        actMsg += " " + it;
    this->_globText.setString(actMsg);
    window->draw(this->_globText);
    this->_list.displayButtons(window);
}

std::string RType::MessagePanel::decyptMessage(const Utils::MessageParsed_s &msg)
{
    std::string toRet = "";
    for (int i = 0; i < 7; ++i) {
        if (msg.bytes[i] < 1)
            break;
        toRet += " " + this->_alltexts[msg.bytes[i] - 1];
    }
    return toRet;
}
