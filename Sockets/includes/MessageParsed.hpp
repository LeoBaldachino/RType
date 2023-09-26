/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** messageStruct
*/

#pragma once
#include <iostream>

namespace RType {
    namespace Utils {
        class MessageParsed_s {
            public :
                MessageParsed_s() {
                    for (int i = 0; i < 7; ++i)
                        this->bytes[i] = 0;
                    senderIp = "";
                    senderPort = 0;
                    msgType = 0;
                };
                ~MessageParsed_s() {};
                MessageParsed_s &operator=(const MessageParsed_s &newMsg) {
                    msgType = newMsg.msgType;
                    for (int i = 0; i < 7; ++i)
                        this->bytes[i] = newMsg.bytes[i];
                    senderIp = newMsg.senderIp;
                    senderPort = newMsg.senderPort;
                    return *this;
                }
                unsigned char msgType;
                unsigned char bytes[7];
                std::string senderIp;
                unsigned short senderPort;
        };
    }
}