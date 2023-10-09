/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PlayerSystem.hpp
*/

#pragma once
#include <memory>
#include "../Entity/Player.hpp"
#include "Subsystems/InputSystem.hpp"
#include "Subsystems/ShotSystem.hpp"
#include "Subsystems/PiercingShotSystem.hpp"

class PlayerSystem {
    public:
        PlayerSystem() {};
        ~PlayerSystem() {};
        void setPlayer(const Player &p);
        Player getPlayer(void) const;
        void getInputs(void);
        void updatePos(void);
        void createShots(Core &core);
        void createPiercingShots(void);
    private:
        Player _player;
        InputSystem _inputSystem;
};