/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotSystem.hpp
*/

#pragma once
#include "../../Entity/PiercingShotEntity.hpp"
#include "ShotSystem.hpp"

class PiercingShotSystem {
    public:
        PiercingShotSystem() {};
        ~PiercingShotSystem() {};
        void updatePos(PiercingShotEntity &pS);
        Position getPos(PiercingShotEntity &pS) const;
    private:
};
