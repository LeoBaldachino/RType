/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotSystem.hpp
*/

#pragma once
#include <memory>
#include "../../Core/Core.hpp"
#include "../../Components/Position.hpp"
#include "../../Entity/ShotEntity.hpp"

class ShotSystem {
    public:
        ShotSystem() {};
        ~ShotSystem() {};
        void updatePos(ShotEntity &s);
        void clearShots(ShotEntity &s, Core &core);
        Position getPos(ShotEntity &s) const;
    private:
};
