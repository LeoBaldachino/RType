/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MessageParsed
*/

#include "../includes/MessageParsed.hpp"

RType::Utils::MessageParsed_s::MessageParsed_s() 
{
    for (int i = 0; i < 7; ++i)
        this->bytes[i] = 0;
    senderIp = "";
    senderPort = 0;
    msgType = 0;
}

RType::Utils::MessageParsed_s::MessageParsed_s(unsigned char type, const std::string &ip, unsigned short port, unsigned char allBytes[7])
{
    for (int i = 0; i < 7; ++i)
        this->bytes[i] = allBytes[i];
    senderIp = ip;
    senderPort = port;
    msgType = type;
}

RType::Utils::MessageParsed_s::MessageParsed_s(unsigned long toDecode, const std::string &ip, unsigned short port)
{
    this->msgType = (toDecode & 0x0000000000000ff);
    this->bytes[0] = (toDecode & 0x0000000000ff00) >> 8;
    this->bytes[1] = (toDecode & 0x00000000ff0000) >> 16;
    this->bytes[2] = (toDecode & 0x000000ff000000) >> 24;
    this->bytes[3] = (toDecode & 0x0000ff00000000) >> 32;
    this->bytes[4] = (toDecode & 0x00ff0000000000) >> 40;
    this->bytes[5] = (toDecode & 0xff000000000000) >> 48;
    this->bytes[6] = (toDecode & 0xff00000000000000) >> 56;
    if (this->msgType == 0)
        this->msgType = 33;
    this->senderIp = ip;
    this->senderPort = port;
}

RType::Utils::MessageParsed_s::MessageParsed_s(const MessageParsed_s &newMsg) 
{
    msgType = newMsg.msgType;
    for (int i = 0; i < 7; ++i)
        this->bytes[i] = newMsg.bytes[i];
    senderIp = newMsg.senderIp;
    senderPort = newMsg.senderPort;
}

RType::Utils::MessageParsed_s::~MessageParsed_s() 
{

};

RType::Utils::MessageParsed_s &RType::Utils::MessageParsed_s::operator=(const MessageParsed_s &newMsg) 
{
    msgType = newMsg.msgType;
    for (int i = 0; i < 7; ++i)
        this->bytes[i] = newMsg.bytes[i];
    senderIp = newMsg.senderIp;
    senderPort = newMsg.senderPort;
    return *this;
}

bool RType::Utils::MessageParsed_s::operator!=(const MessageParsed_s &newMsg) 
{
    if (msgType != newMsg.msgType)
        return true;
    for (int i = 0; i < 7; ++i)
        if (this->bytes[i] != newMsg.bytes[i])
            return true;
    if (senderIp != newMsg.senderIp)
        return true;
    if (senderPort != newMsg.senderPort)
        return true;
    return false;
}

bool RType::Utils::MessageParsed_s::operator==(const MessageParsed_s &newMsg) 
{
    if (msgType != newMsg.msgType)
        return false;
    for (int i = 0; i < 7; ++i)
        if (this->bytes[i] != newMsg.bytes[i])
            return false;
    if (senderIp != newMsg.senderIp)
        return false;
    if (senderPort != newMsg.senderPort)
        return false;
    return true;
}

unsigned long RType::Utils::MessageParsed_s::encode() const
{
    return 
       static_cast<unsigned long>(this->bytes[6]) << 56 |
       static_cast<unsigned long>(this->bytes[5]) << 48 |
       static_cast<unsigned long>(this->bytes[4]) << 40 |
       static_cast<unsigned long>(this->bytes[3]) << 32 |
       static_cast<unsigned long>(this->bytes[2]) << 24 |
       static_cast<unsigned long>(this->bytes[1]) << 16 |
       static_cast<unsigned long>(this->bytes[0]) << 8  |
       static_cast<unsigned long>(this->msgType);
}

unsigned short RType::Utils::MessageParsed_s::getFirstShort() const
{
    return static_cast<unsigned short>(this->bytes[1]) << 8 | static_cast<unsigned short>(this->bytes[0]); 
}

void RType::Utils::MessageParsed_s::setFirstShort(unsigned short toDecode)
{
    this->bytes[0] = (toDecode & 0xff);
    this->bytes[1] = (toDecode & 0x000000ff00) >> 8; 
}

unsigned short RType::Utils::MessageParsed_s::getSecondShort() const
{
    return static_cast<unsigned short>(this->bytes[3]) << 8 | static_cast<unsigned short>(this->bytes[2]); 
}

void RType::Utils::MessageParsed_s::setSecondShort(unsigned short toDecode)
{
    this->bytes[2] = (toDecode & 0xff);
    this->bytes[3] = (toDecode & 0x000000ff00) >> 8; 
}

unsigned short RType::Utils::MessageParsed_s::getThirdShort() const
{
    return static_cast<unsigned short>(this->bytes[5]) << 8 | static_cast<unsigned short>(this->bytes[4]); 
}

void RType::Utils::MessageParsed_s::setThirdShort(unsigned short toDecode)
{
    this->bytes[4] = (toDecode & 0xff);
    this->bytes[5] = (toDecode & 0x000000ff00) >> 8; 
}
