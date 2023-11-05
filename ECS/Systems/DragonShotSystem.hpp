/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DragonShotSystem.hpp
*/

#pragma once
#include "../Entity/DragonShot.hpp"
#include "../../Core/Core.hpp"
#include "Subsystems/HitBox.hpp"

class DragonShotSystem {
    public:
        DragonShotSystem() {};
        ~DragonShotSystem() {};
        void updatePos(DragonShot &dS, Position lastPlayerPos);
        void checkCollision(DragonShot &dS, IEntity &entity, Core &core, bool isTouching);
    private:
        HitBox _hitBoxSystem;
};
