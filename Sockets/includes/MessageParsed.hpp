/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** messageStruct
*/

#pragma once
#include <iostream>
#include <ostream>

namespace RType {
    namespace Utils {
        class MessageParsed_s {
            public :
                /**
                 * @brief Construct a new MessageParsed_s object empty
                 * 
                 */
                MessageParsed_s();
                /**
                 * @brief Construct a new MessageParsed_s object with all the details
                 * 
                 * @param type msgType
                 * @param ip senderIp
                 * @param port sendPort
                 * @param allBytes bytes
                 */
                MessageParsed_s(unsigned char type, const std::string &ip, unsigned short port, unsigned char allBytes[7]);
                /**
                 * @brief Construct a new MessageParsed_s object by copy
                 * 
                 * @param newMsg the message to copy
                 */
                MessageParsed_s(const MessageParsed_s &newMsg);
                /**
                 * @brief Destroy the MessageParsed_s object
                 * 
                 */
                ~MessageParsed_s();
                /**
                 * @brief equal operator
                 * 
                 * @param newMsg message to make equal to this class
                 * @return MessageParsed_s& reference to this object
                 */
                MessageParsed_s &operator=(const MessageParsed_s &newMsg);
                /**
                 * @brief different operator
                 * 
                 * @param newMsg message to compare
                 * @return true if they are different
                 * @return false otherwise
                 */
                bool operator!=(const MessageParsed_s &newMsg);
                /**
                 * @brief equal operator
                 * 
                 * @param newMsg message to compare
                 * @return true if they are the same
                 * @return false otherwise
                 */
                bool operator==(const MessageParsed_s &newMsg);
                /**
                 * @brief Get the First Short value
                 * 
                 * @return unsigned short the first short value
                 */
                unsigned short getFirstShort() const;
                /**
                 * @brief Get the Second Short value
                 * 
                 * @return unsigned short the second short value
                 */
                unsigned short getSecondShort() const;
                /**
                 * @brief Get the Third Short value
                 * 
                 * @return unsigned short the third short value
                 */
                unsigned short getThirdShort() const;
                /**
                 * @brief Set the First Short value, if the first two bytes are set it will override their values
                 * 
                 * @param toSet value to set
                 */
                void setFirstShort(unsigned short toSet);
                /**
                 * @brief Set the Second Short value, if the third and fourth bytes are set it will override their values
                 * 
                 * @param toSet value to set
                 */
                void setSecondShort(unsigned short toSet);
                /**
                 * @brief Set the Thirdshort object, if the fifth and sixth bytes are set it will override their values
                 * 
                 * @param toSet 
                 */
                void setThirdShort(unsigned short toSet);

                unsigned char msgType;
                unsigned char bytes[7];
                std::string senderIp;
                unsigned short senderPort;
                friend std::ostream& operator<<(std::ostream& os, const RType::Utils::MessageParsed_s& msg);
                friend std::istream& operator>>(std::istream& is, RType::Utils::MessageParsed_s& msg);
            private :
                /**
                 * @brief encode the message for send him
                 * 
                 * @return unsigned long encoded value
                 */
                unsigned long encode() const;

                MessageParsed_s decode(unsigned long toDecode) const;

        };
        std::ostream& operator<<(std::ostream& os, const RType::Utils::MessageParsed_s& msg);
        std::istream& operator>>(std::istream& is, RType::Utils::MessageParsed_s& msg);
    }
}
