/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** MermaidSystem.hpp
*/

#pragma once
#include "../Entity/Mermaid.hpp"
#include "../Core/Core.hpp"
#include "../Entity/MermaidShot.hpp"
#include "Subsystems/MovementSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/HitBox.hpp"

#include <chrono>

class MermaidSystem {
    public:
        MermaidSystem() {};
        ~MermaidSystem() {};
        void updatePos(Mermaid &t);
        void checkCollision(Mermaid &t, IEntity &entity, Core &core, bool isTouching);
        void shot(Mermaid &t, Core &core);
    private:
        MovementSystem _movementSystem;
        HitBox _hitBoxSystem;
};
