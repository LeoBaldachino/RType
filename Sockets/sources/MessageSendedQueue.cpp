/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MessageSendedQueue
*/

#include "../includes/MessageSendedQueue.hpp"

RType::MessageSendedQueue::MessageSendedQueue(const std::list<int> &importantMessages) : _importantMessages(importantMessages)
{
    this->_delay = std::chrono::steady_clock::now();
    this->_importantMessages.push_back(34);
}

void RType::MessageSendedQueue::addMessage(const Utils::MessageParsed_s &msg)
{
    for (auto it : this->_importantMessages)
        if (it == msg.msgType) {
            this->_queueImportantMessages.push_back(msg);
            return;
        }
    if (this->_queueMessage.size() > MAX_SIZE_MSG_QUEUE)
        this->_queueMessage.clear();
    this->_queueMessage.push_back(msg);
}

RType::Utils::MessageParsed_s RType::MessageSendedQueue::getMessage(bool &isImportant)
{
    // std::cout << "Important size " << this->_queueImportantMessages.size() << std::endl;
    // std::cout << "Normal size    " << this->_queueMessage.size() << std::endl;
    if (!this->_queueImportantMessages.empty()) {
        auto ret = this->_queueImportantMessages.front();
        this->_queueImportantMessages.pop_front();
        isImportant = true;
        return ret;
    }
    isImportant = false;
    if (!this->_queueMessage.empty()) {
        auto ret = this->_queueMessage.front();
        this->_queueMessage.pop_front();
        return ret;
    }
    Utils::MessageParsed_s ret;
    ret.msgType = 33;
    return ret;
}

bool RType::MessageSendedQueue::readyToGetMessage()
{
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::microseconds>(clock - this->_delay).count() < this->_messageDelay) {
        return false;
    }
    this->_delay = clock;
    return true;
}

bool RType::MessageSendedQueue::isImportant(const Utils::MessageParsed_s &msg)
{
    for (auto it : this->_importantMessages)
        if (msg.msgType == it)
            return true;
    return false;
}
