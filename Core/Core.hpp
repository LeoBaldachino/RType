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

class Core {
    public:
        Core();
        ~Core() {};
        void addEntity(const std::shared_ptr<IEntity> &entity);
        std::unordered_map<unsigned short, std::shared_ptr<IEntity>> _entities;
    private:
        SystemVisitor _systemVisitor;
        unsigned short _entityCount = 0;
};
