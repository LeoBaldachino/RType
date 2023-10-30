/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PredictShoot
*/

#pragma once
#include <unordered_map>
#include "../../Components/Position.hpp"
#include "../PlayerSystem.hpp"
#include "../BydosSystem.hpp"

class PredictShoot {
    public:
        PredictShoot();
        ~PredictShoot();
        bool shootSetVector(unsigned short id, ShotEntity &s);
    private:
        void checkShootTooFast(Vector2d &shoot);
        std::unordered_map<unsigned short, std::pair<Vector2d, Vector2d>> _shootPositions;
};
