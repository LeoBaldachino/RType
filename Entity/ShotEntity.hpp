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
#include "IEntity.hpp"

#define SHOT_X 32
#define SHOT_Y 12

class ShotEntity {
    public:
        ShotEntity(Shoot &shoot);
        ~ShotEntity() {};

        Shoot getShoot(void) const;
        void setShoot(const Shoot &shoot);

        Drawable getDrawable(void) const;
        void setDrawable(const Drawable &drawable);
        Vector2d getSize(void);
        bool isColidingWith(IEntity &entity);
    private:
        Shoot _shoot;
        Drawable _drawable;
        Vector2d _size;
};
