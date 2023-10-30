/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PacketTracker
*/

#pragma once
#include "MessageParsed.hpp"
#include <list>
#include <map>
#include <memory>

namespace RType {
    class PacketTracker {
        public:
            PacketTracker();
            ~PacketTracker() {};
            void prepareMessageToSend(Utils::MessageParsed_s &msg);
            bool receiveMessage(const Utils::MessageParsed_s &msg, std::list<Utils::MessageParsed_s> &toFill);
            bool reSendMessage(Utils::MessageParsed_s &toFill, const Utils::MessageParsed_s &msg);
        private:
            void messagesToResend(std::map<std::pair<std::string, int>, std::shared_ptr<std::list<unsigned char>>>::iterator &find, std::list<Utils::MessageParsed_s> &toFill);
            std::map<std::pair<std::string, int>, std::shared_ptr<std::list<Utils::MessageParsed_s>>> _sendedMessages;
            std::map<std::pair<std::string, int>, unsigned char> _clientCountersMessages;
            std::map<std::pair<std::string, int>, std::shared_ptr<std::list<unsigned char>>> _messagesNeededToGet;
            std::list<Utils::MessageParsed_s> _messagesToResend;
            std::pair<unsigned char, unsigned char> _interval;
            bool _intervalSet;
    };
}
