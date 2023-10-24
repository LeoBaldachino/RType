/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MessageSendedQueue
*/

#pragma once
#include <vector>
#include <chrono>
#include <list>
#include "MessageParsed.hpp"
#define MAX_SIZE_MSG_QUEUE 50
#define MESSAGE_DELAY 10000

namespace RType {
    class MessageSendedQueue {
        public:
            MessageSendedQueue(const std::list<int> &importantMessages);
            ~MessageSendedQueue();
            void addMessage(const Utils::MessageParsed_s &msg);
            Utils::MessageParsed_s getMessage(bool &isImportant);
            bool readyToGetMessage();
            bool isImportant(const Utils::MessageParsed_s &msg);
            inline bool empty() {return (this->_queueImportantMessages.empty() && this->_queueMessage.empty());};
        private:
            std::list<Utils::MessageParsed_s> _queueMessage;
            std::list<Utils::MessageParsed_s> _queueImportantMessages;
            std::chrono::steady_clock::time_point _delay;
            std::list<int> _importantMessages;
    };
}
