/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** IEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include <queue>
#include "../Components/Moveable.hpp"
#include "../Components/Position.hpp"
#include "../Visitor/IVisitor.hpp"
#include "../Sockets/includes/MessageParsed.hpp"

class IEntity {
    public:
        virtual void accept(IVisitor &v) = 0;
        virtual void setMoveable(const Moveable &moveable) = 0;
        virtual Moveable getMoveable(void) const = 0;
        virtual void setPosition(const Position &position) = 0;
        virtual Position getPosition(void) const = 0;
        virtual void addMessage(RType::Utils::MessageParsed_s &message) = 0;
        virtual void popMessage(void) = 0;
};
