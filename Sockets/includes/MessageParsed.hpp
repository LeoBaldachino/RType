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
        template<typename T>
        struct MessageParsed_s {
            unsigned char msgType;
            unsigned int sender;
            T data;
            size_t dataSize;
        };
    }
}