/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** PiercingShotEntity.hpp
*/

#pragma once
#include <fstream>
#include <iostream>
#include "../Components/Shoot.hpp"
#include "../Components/Drawable.hpp"

class PiercingShotEntity {
    public:
        PiercingShotEntity(Shoot &shoot);
        ~PiercingShotEntity() {};

        Shoot getShoot(void) const;
        void setShoot(const Shoot &shoot);

        Drawable getDrawable(void) const;
        void setDrawable(const Drawable &drawable);
    private:
        Shoot _shoot;
        Drawable _drawable;
};
