/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** ShotEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "../Components/Drawable.hpp"

class ShotEntity {
    public:
        ShotEntity(Shoot &shoot);
        ~ShotEntity() {};

        Shoot getShoot(void) const;
        void setShoot(const Shoot &shoot);

        Drawable getDrawable(void) const;
        void setDrawable(const Drawable &drawable);
    private:
        Shoot _shoot;
        Drawable _drawable;
};
