/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PacketTracker
*/

#include "../includes/PacketTracker.hpp"

RType::PacketTracker::PacketTracker()
{
    this->_intervalSet = false;
}

RType::PacketTracker::~PacketTracker()
{
}

void RType::PacketTracker::prepareMessageToSend(Utils::MessageParsed_s &msg)
{
    std::pair<std::string, int> clientToSend = std::make_pair(msg.senderIp, msg.senderPort);
    if (this->_sendedMessages.empty())
        std::cout << "Empty !" << std::endl;
    auto find = this->_sendedMessages.find(clientToSend);
    if (find == this->_sendedMessages.end()) {
        this->_sendedMessages.insert({clientToSend, std::make_shared<std::list<Utils::MessageParsed_s>>()});
        this->_clientCountersMessages.insert({clientToSend, 0});
        this->_messagesNeededToGet.insert({clientToSend, std::make_shared<std::list<unsigned char>>()});
        find = this->_sendedMessages.find(clientToSend);
    }
    if (find->second->size() >= 254)
        find->second->clear();
    unsigned char actId = static_cast<unsigned char>(find->second->size());
    msg.bytes[6] = actId;
    find->second->push_back(msg);
}

bool RType::PacketTracker::receiveMessage(const Utils::MessageParsed_s &msg, std::list<Utils::MessageParsed_s> &toFill)
{
    std::pair<std::string, int> clientToSend = std::make_pair(msg.senderIp, msg.senderPort);
    auto find = this->_clientCountersMessages.find(clientToSend);
    auto findMsg = this->_messagesNeededToGet.find(clientToSend);
    if (find == this->_clientCountersMessages.end()) {
        this->_sendedMessages.insert({clientToSend, std::make_shared<std::list<Utils::MessageParsed_s>>()});
        this->_clientCountersMessages.insert({clientToSend, 0});
        this->_messagesNeededToGet.insert({clientToSend, std::make_shared<std::list<unsigned char>>()});
        return true;
    }
    for (auto it = findMsg->second->begin(); it != findMsg->second->end(); it++)
        if (*it == msg.bytes[6]) {
            findMsg->second->erase(it);
            return true;
        }
    find->second++;
    if (find->second >= 254) {
        find->second = 0;
        std::cout << "Reset find..." << std::endl;
    }
    if (find->second != msg.bytes[6]) {
        this->_interval = {find->second, msg.bytes[6]};
        std::cout << "Packet loss detected from " << static_cast<int>(this->_interval.first) << " to " << static_cast<int>(this->_interval.second) << std::endl;
        this->_intervalSet = true;
        this->messagesToResend(findMsg, toFill);
        this->_intervalSet = false;
        find->second = msg.bytes[6];
        return false;
    }
    return false;
}

void RType::PacketTracker::messagesToResend(std::map<std::pair<std::string, int>, std::shared_ptr<std::list<unsigned char>>>::iterator &listMessages, std::list<Utils::MessageParsed_s> &toFill)
{
    if (!this->_intervalSet)
        return;
    Utils::MessageParsed_s msg;
    msg.msgType = 34;
    for (unsigned char i = this->_interval.first; i < this->_interval.second; ++i) {
        listMessages->second->push_back(i);
        msg.bytes[0] = i;
        msg.senderIp = listMessages->first.first;
        msg.senderPort = listMessages->first.second;
    }
}

bool RType::PacketTracker::reSendMessage(Utils::MessageParsed_s &toFill, const Utils::MessageParsed_s &msg)
{
    if (msg.msgType != 34)
        return false;
    std::pair<std::string, int> player(msg.senderIp, msg.senderPort);
    auto find = this->_sendedMessages.find(player);
    if (find == this->_sendedMessages.end())
        return false;
    for (auto it : (*find->second)) {
        if (it.bytes[6] == msg.bytes[6])
            toFill = it;
            return true;
    }
    return false;
}
