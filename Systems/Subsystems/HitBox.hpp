/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** HitBox
*/

#pragma once
#include "../../Entity/IEntity.hpp"
#include "../../Components/Moveable.hpp"
#include "../../Components/Position.hpp"

class HitBox {
    public:
        HitBox() {};
        ~HitBox() {};
        bool entityIntersect(IEntity &first, IEntity &sec);
    private:
};
