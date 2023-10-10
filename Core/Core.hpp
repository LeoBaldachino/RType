/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Core.hpp
*/

#pragma once
#include "../Entity/IEntity.hpp"
#include <unordered_map>
#include <memory>
#include <climits>
#include <list>

class Core {
    public:
        Core() {};
        ~Core() {};
        bool addEntity(const std::shared_ptr<IEntity> &entity, unsigned short index);
        std::unordered_map<unsigned short, std::shared_ptr<IEntity>> _entities;
        unsigned short getAvailabeIndex();
        bool removeEntity(unsigned short index);
        bool removeEntity(IEntity &entity);
        bool removeEntityLater(unsigned short index);
        bool removeEntityLater(IEntity &entity);
        void eraseEntity(void);
    private:
        std::queue<unsigned short> _presentIndex;
        std::queue<unsigned short> _erase;
};
