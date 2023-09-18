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
        typedef struct MessageParsed_s {
            unsigned char msgType;
            unsigned int sender;
            const void *data;
            size_t dataSize;
        } MessageParsed_t;
    }
}