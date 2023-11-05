/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** GenieShotSystem.hpp
*/

#pragma once
#include "../Entity/GenieShot.hpp"
#include "../../Core/Core.hpp"
#include "Subsystems/HitBox.hpp"

class GenieShotSystem {
    public:
        GenieShotSystem() {};
        ~GenieShotSystem() {};
        void updatePos(GenieShot &gS);
        void checkCollision(GenieShot &gS, IEntity &entity, Core &core, bool isTouching);
    private:
        HitBox _hitBoxSystem;
};
