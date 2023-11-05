/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MermaidShotSystem.hpp
*/

#pragma once
#include "../Entity/MermaidShot.hpp"
#include "../../Core/Core.hpp"
#include "Subsystems/HitBox.hpp"

class MermaidShotSystem {
    public:
        MermaidShotSystem() {};
        ~MermaidShotSystem() {};
        void updatePos(MermaidShot &dS, Position lastPlayerPos);
        void checkCollision(MermaidShot &dS, IEntity &entity, Core &core, bool isTouching);
    private:
        HitBox _hitBoxSystem;
};
