/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Core.hpp
*/

#pragma once
#include <memory>
#include "../Entity/Player.hpp"
#include "../Entity/Bydos.hpp"
#include "../Visitor/SystemVisitor.hpp"
#include <climits>
#include <list>

class Core {
    public:
        Core();
        ~Core() {};
        bool addEntity(const std::shared_ptr<IEntity> &entity, unsigned short index);
        std::unordered_map<unsigned short, std::shared_ptr<IEntity>> _entities;
        unsigned short getAvailabeIndex();
        bool removeEntity(unsigned short index);
    private:
        SystemVisitor _systemVisitor;
        std::queue<unsigned short> _presentIndex;

};
