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

#define SIZE_SCALE 2

class IEntity {
    public:
        virtual void accept(IVisitor &v) = 0;
        virtual void setMoveable(const Moveable &moveable) = 0;
        virtual Moveable getMoveable(void) const = 0;
        virtual void setPosition(const Position &position) = 0;
        virtual Position getPosition(void) const = 0;
        virtual bool isColidingWith(IEntity &entity) = 0; 
        virtual Vector2d getSize(void) = 0;

        // virtual void accept(IVisitor &v, Player &p, std::unique_ptr<sf::RenderWindow> &window) = 0;
};
