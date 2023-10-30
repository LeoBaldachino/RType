/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.hpp
*/

#pragma once
#include <memory>
#include "../Entity/Player.hpp"
#include "../Core/Core.hpp"
#include "Subsystems/InputSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/PiercingShotSystem.hpp"
#include "Subsystems/HitBox.hpp"


class PlayerSystem {
    public:
        PlayerSystem() {};
        ~PlayerSystem() {};
        void updatePos(Player &p);
        void createShots(Player &p, Core &core);
        void checkCollision(Player &p, IEntity &entity, Core &core);
    private:
        InputSystem _inputSystem;
        HitBox _hitBoxSystem;
};
